#include <iostream>
#include <memory>

#include "Block/BlockManager.hpp"
#include "Block/ClockBlock.hpp"
#include "Block/SineBlock.hpp"
#include "Block/CosineBlock.hpp"
#include "Block/ScopeBlock.hpp"
#include "Block/AddBlock.hpp"
#include "Block/MultiplyBlock.hpp"
#include "Block/GainBlock.hpp"

#include "Graph/ConnectionManager.hpp"

#include "Engine/GraphExecutionEngine.hpp"
#include "Engine/SimulationScheduler.hpp"

#include "Graph/ProjectSerializer.hpp"

#include <nlohmann/json.hpp>

using namespace pass::simulink;
using json = nlohmann::json;

int main(){
    BlockManager blockManager;

    auto clock = std::make_unique<ClockBlock>();
    clock->setId("Clock_1");

    auto sine = std::make_unique<SineBlock>();
    sine->setId("Sine_1");

    auto add = std::make_unique<AddBlock>();
    add->setId("Add_1");

    auto gain = std::make_unique<GainBlock>(2.0);
    gain->setId("Gain_1");

    auto scope = std::make_unique<ScopeBlock>();
    scope->setId("Scope_1");

    blockManager.addBlock(std::move(clock));
    blockManager.addBlock(std::move(sine));
    blockManager.addBlock(std::move(add));
    blockManager.addBlock(std::move(gain));
    blockManager.addBlock(std::move(scope));

    ConnectionManager graph;

    // Clock_1 -> Sine_1  (Sine only has one input, port 0)
    graph.connect(blockManager, "Clock_1", "Sine_1", 0, 0);
    // Clock_1 -> Add_1   (port 0 of Add_1)
    graph.connect(blockManager, "Clock_1", "Add_1",  0, 0);
    // Sine_1  -> Add_1   (port 1 of Add_1)
    graph.connect(blockManager, "Sine_1",  "Add_1",  0, 1);
    // Add_1  -> Gain_1
    graph.connect(blockManager, "Add_1",   "Gain_1", 0, 0);
    // Gain_1 -> Scope_1
    graph.connect(blockManager, "Gain_1",  "Scope_1", 0, 0);

    // --- Print connections as JSON ---
    {
        json connList = json::array();
        for (const auto& c : graph.getConnections()){
            json entry;
            entry["from"]     = c.from;
            entry["fromPort"] = c.fromPort;
            entry["to"]       = c.to;
            entry["toPort"]   = c.toPort;
            connList.push_back(entry);
        }
        json out;
        out["event"]       = "graph_built";
        out["connections"] = connList;
        std::cout << out.dump(4) << "\n";
    }

    GraphExecutionEngine engine(blockManager, graph);
    SimulationScheduler scheduler(engine, 0.0, 1.0, 0.2);

    // --- Print simulation start as JSON ---
    {
        json out;
        out["event"]     = "simulation_start";
        out["startTime"] = scheduler.getStartTime();
        out["endTime"]   = scheduler.getEndTime();
        out["stepSize"]  = scheduler.getStepSize();
        std::cout << out.dump(4) << "\n";
    }

    scheduler.run();

    // --- Print scope results as JSON ---
    {
        const auto* scopePtr = dynamic_cast<const ScopeBlock*>(blockManager.getBlock("Scope_1"));
        json out;
        out["event"]  = "simulation_end";
        out["scope"]  = "Scope_1";
        out["values"] = scopePtr ? scopePtr->getValues() : std::vector<double>{};
        std::cout << out.dump(4) << "\n";
    }

    // ==========================================================
    // JSON SAVE / LOAD
    // ==========================================================
    const std::string projectFile = "project.json";

    bool saved = ProjectSerializer::saveToFile(projectFile, blockManager, graph, scheduler);
    {
        json out;
        out["event"]  = saved ? "save_ok" : "save_failed";
        out["file"]   = projectFile;
        std::cout << out.dump(4) << "\n";
    }
    if (!saved) return 1;

    // --- Load into fresh objects ---
    BlockManager      bm2;
    ConnectionManager g2;
    GraphExecutionEngine engine2(bm2, g2);
    SimulationScheduler  scheduler2(engine2, 0.0, 0.0, 1.0);

    bool loaded = ProjectSerializer::loadFromFile(projectFile, bm2, g2, scheduler2);
    {
        json out;
        out["event"] = loaded ? "load_ok" : "load_failed";
        out["file"]  = projectFile;
        if (loaded){
            out["startTime"] = scheduler2.getStartTime();
            out["endTime"]   = scheduler2.getEndTime();
            out["stepSize"]  = scheduler2.getStepSize();
        }
        std::cout << out.dump(4) << "\n";
    }
    if (!loaded) return 1;

    // --- Re-run from loaded project ---
    {
        json out;
        out["event"] = "rerun_start";
        out["source"] = projectFile;
        std::cout << out.dump(4) << "\n";
    }

    scheduler2.run();

    // --- Print loaded scope results as JSON ---
    {
        const auto* scopePtr2 = dynamic_cast<const ScopeBlock*>(bm2.getBlock("Scope_1"));
        json out;
        out["event"]  = "rerun_end";
        out["scope"]  = "Scope_1";
        out["values"] = scopePtr2 ? scopePtr2->getValues() : std::vector<double>{};
        std::cout << out.dump(4) << "\n";
    }

    {
        json out;
        out["event"]  = "round_trip_complete";
        out["status"] = "ok";
        std::cout << out.dump(4) << "\n";
    }

    return 0;
}
