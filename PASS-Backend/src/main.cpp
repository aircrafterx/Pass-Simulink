










#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <cmath>


#include <nlohmann/json.hpp>


#include <httplib.h>


#include "Block/BlockManager.hpp"
#include "Block/BlockFactory.hpp"
#include "Block/ClockBlock.hpp"
#include "Block/ScopeBlock.hpp"

#include "Graph/ConnectionManager.hpp"
#include "Graph/ProjectSerializer.hpp"

#include "Engine/GraphExecutionEngine.hpp"
#include "Engine/SimulationScheduler.hpp"

using namespace pass::simulink;
using json = nlohmann::json;



static const std::string PROJECT_FILE = "project.json";
static const int         SERVER_PORT  = 8085;


static void addCorsHeaders(httplib::Response& res)
{
    res.set_header("Access-Control-Allow-Origin",  "*");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
}

static void jsonResponse(httplib::Response& res, int status, const json& body)
{
    addCorsHeaders(res);
    res.status       = status;
    res.set_content(body.dump(2), "application/json");
}





static json buildCatalog()
{
    json catalog = json::array();

    auto entry = [&](const std::string& type,
                     const std::string& category,
                     int inputs, int outputs,
                     json defaultParams)
    {
        json e;
        e["type"]          = type;
        e["category"]      = category;
        e["inputs"]        = inputs;
        e["outputs"]       = outputs;
        e["defaultParams"] = defaultParams;
        catalog.push_back(e);
    };

    entry("Clock",    "Sources", 0, 1, { {"stepSize", 1.0} });
    entry("Sine",     "Sources", 1, 1, { {"amplitude", 1.0}, {"frequency", 1.0}, {"phaseOffset", 0.0} });
    entry("Cosine",   "Sources", 1, 1, { {"amplitude", 1.0}, {"frequency", 1.0}, {"phaseOffset", 0.0} });
    entry("Gain",     "Math",    1, 1, { {"gain", 1.0} });
    entry("Add",      "Math",    2, 1, json::object());
    entry("Subtract", "Math",    2, 1, json::object());
    entry("Multiply", "Math",    2, 1, json::object());
    entry("Average",  "Math",    2, 1, json::object());
    entry("Min",      "Math",    2, 1, json::object());
    entry("Max",      "Math",    2, 1, json::object());
    entry("Scope",    "Sinks",   1, 0, json::object());

    return catalog;
}





static json runSimulation(const json& project)
{
    BlockManager      blockManager;
    ConnectionManager graph;


    if (!project.contains("blocks") || !project["blocks"].is_array()) {
        return { {"error", "Missing 'blocks' array"} };
    }
    for (const auto& entry : project["blocks"]) {
        std::string type = entry.value("type", "");
        std::string id   = entry.value("id",   "");
        double x         = entry.value("x",    0.0);
        double y         = entry.value("y",    0.0);

        auto block = BlockFactory::createBlock(type);
        if (!block) continue;

        block->setId(id);
        block->setX(x);
        block->setY(y);

        if (entry.contains("params") && entry["params"].is_object()) {
            std::map<std::string,double> pm;
            for (const auto& [k, v] : entry["params"].items())
                if (v.is_number()) pm[k] = v.get<double>();
            block->setParameters(pm);
        }
        blockManager.addBlock(std::move(block));
    }


    if (!project.contains("connections") || !project["connections"].is_array()) {
        return { {"error", "Missing 'connections' array"} };
    }
    for (const auto& entry : project["connections"]) {
        std::string from = entry.value("from", "");
        std::string to   = entry.value("to",   "");
        int fromPort     = entry.value("fromPort", 0);
        int toPort       = entry.value("toPort",   0);
        graph.connect(blockManager, from, to, fromPort, toPort);
    }


    double startTime = 0.0, endTime = 10.0, stepSize = 0.1;
    if (project.contains("settings") && project["settings"].is_object()) {
        const auto& s = project["settings"];
        startTime = s.value("startTime", 0.0);
        endTime   = s.value("endTime",   10.0);
        stepSize  = s.value("stepSize",  0.1);
    }

    GraphExecutionEngine engine(blockManager, graph);
    SimulationScheduler scheduler(engine, startTime, endTime, stepSize);


    std::ostringstream tickBuffer;
    std::streambuf* origBuf = std::cout.rdbuf(tickBuffer.rdbuf());

    scheduler.run();

    std::cout.rdbuf(origBuf);


    json scopeResults = json::object();
    for (const auto& [id, block] : blockManager.getBlocks()) {
        if (block->getType() == "Scope") {
            const auto* scope = dynamic_cast<const ScopeBlock*>(block.get());
            if (scope) {
                scopeResults[id] = scope->getValues();
            }
        }
    }


    json ticks = json::array();
    std::istringstream stream(tickBuffer.str());
    std::string line;
    std::string accumulated;
    int braceDepth = 0;

    for (std::string rawLine; std::getline(stream, rawLine); ) {
        accumulated += rawLine + "\n";
        for (char ch : rawLine) {
            if (ch == '{') braceDepth++;
            if (ch == '}') braceDepth--;
        }
        if (braceDepth == 0 && !accumulated.empty()) {
            try {
                json obj = json::parse(accumulated);
                if (obj.contains("tick")) {
                    ticks.push_back(obj);
                }
            } catch (...) {}
            accumulated.clear();
        }
    }

    json result;
    result["status"]    = "ok";
    result["startTime"] = startTime;
    result["endTime"]   = endTime;
    result["stepSize"]  = stepSize;
    result["ticks"]     = ticks;
    result["scopes"]    = scopeResults;
    return result;
}



int main()
{
    httplib::Server svr;

    std::cout << "[PASS-Backend] Starting HTTP API server on port "
              << SERVER_PORT << " ...\n";


    svr.Options(".*", [](const httplib::Request&, httplib::Response& res) {
        addCorsHeaders(res);
        res.status = 204;
    });


    svr.Get("/api/blocks/catalog", [](const httplib::Request&, httplib::Response& res) {
        jsonResponse(res, 200, buildCatalog());
    });


    svr.Post("/api/simulate", [](const httplib::Request& req, httplib::Response& res) {
        json project;
        try {
            project = json::parse(req.body);
        } catch (const json::parse_error& e) {
            jsonResponse(res, 400, { {"error", std::string("JSON parse error: ") + e.what()} });
            return;
        }

        json result = runSimulation(project);
        int  status = result.contains("error") ? 422 : 200;
        jsonResponse(res, status, result);
    });


    svr.Post("/api/save", [](const httplib::Request& req, httplib::Response& res) {
        json project;
        try {
            project = json::parse(req.body);
        } catch (const json::parse_error& e) {
            jsonResponse(res, 400, { {"error", std::string("JSON parse error: ") + e.what()} });
            return;
        }

        std::ofstream file(PROJECT_FILE);
        if (!file.is_open()) {
            jsonResponse(res, 500, { {"error", "Cannot write " + PROJECT_FILE} });
            return;
        }
        file << project.dump(4);
        file.close();
        jsonResponse(res, 200, { {"status", "saved"}, {"file", PROJECT_FILE} });
    });


    svr.Get("/api/load", [](const httplib::Request&, httplib::Response& res) {
        std::ifstream file(PROJECT_FILE);
        if (!file.is_open()) {
            jsonResponse(res, 404, { {"error", "No saved project found"} });
            return;
        }
        json project;
        try {
            file >> project;
        } catch (const json::parse_error& e) {
            jsonResponse(res, 500, { {"error", std::string("JSON parse error: ") + e.what()} });
            return;
        }
        jsonResponse(res, 200, project);
    });


    std::cout << "[PASS-Backend] Ready. Listening on http://localhost:"
              << SERVER_PORT << "\n";
    std::cout << "[PASS-Backend] Endpoints:\n"
              << "   GET  /api/blocks/catalog\n"
              << "   POST /api/simulate\n"
              << "   POST /api/save\n"
              << "   GET  /api/load\n";

    if (!svr.listen("0.0.0.0", SERVER_PORT)) {
        std::cerr << "[PASS-Backend] ERROR: Failed to bind port " << SERVER_PORT << "\n";
        return 1;
    }

    return 0;
}
