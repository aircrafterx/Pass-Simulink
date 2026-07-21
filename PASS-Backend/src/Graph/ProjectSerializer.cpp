#include "Graph/ProjectSerializer.hpp"
#include "Block/BlockFactory.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace pass::simulink{





    bool ProjectSerializer::saveToFile(const std::string& filename,
                                       const BlockManager& blocks,
                                       const ConnectionManager& graph,
                                       const SimulationScheduler& scheduler)
    {
        json project;


        json blocksArray = json::array();
        for (const auto& [id, block] : blocks.getBlocks()){
            json entry;
            entry["id"]   = block->getId();
            entry["type"] = block->getType();
            entry["x"]    = block->getX();
            entry["y"]    = block->getY();


            json paramsJson = json::object();
            for (const auto& [key, val] : block->getParameters()){
                paramsJson[key] = val;
            }
            entry["params"] = paramsJson;
            blocksArray.push_back(entry);
        }
        project["blocks"] = blocksArray;


        json connectionsArray = json::array();
        for (const auto& conn : graph.getConnections()){
            json entry;
            entry["from"]     = conn.from;
            entry["to"]       = conn.to;
            entry["fromPort"] = conn.fromPort;
            entry["toPort"]   = conn.toPort;
            connectionsArray.push_back(entry);
        }
        project["connections"] = connectionsArray;


        project["settings"] = {
            {"startTime", scheduler.getStartTime()},
            {"endTime",   scheduler.getEndTime()},
            {"stepSize",  scheduler.getStepSize()}
        };


        std::ofstream file(filename);
        if (!file.is_open()){
            std::cerr << "[ProjectSerializer] ERROR: Cannot open file for writing: " << filename << "\n";
            return false;
        }

        file << project.dump(4);
        file.close();

        std::cout << "[ProjectSerializer] Project saved to: " << filename << "\n";
        return true;
    }





    bool ProjectSerializer::loadFromFile(const std::string& filename,
                                         BlockManager& blocks,
                                         ConnectionManager& graph,
                                         SimulationScheduler& scheduler)
    {
        std::ifstream file(filename);
        if (!file.is_open()){
            std::cerr << "[ProjectSerializer] ERROR: Cannot open file for reading: " << filename << "\n";
            return false;
        }

        json project;
        try {
            file >> project;
        } catch (const json::parse_error& e){
            std::cerr << "[ProjectSerializer] ERROR: JSON parse error: " << e.what() << "\n";
            return false;
        }
        file.close();


        if (!project.contains("blocks") || !project["blocks"].is_array()){
            std::cerr << "[ProjectSerializer] ERROR: Missing or invalid 'blocks' array.\n";
            return false;
        }

        for (const auto& entry : project["blocks"]){
            std::string type = entry["type"].get<std::string>();
            std::string id   = entry["id"].get<std::string>();
            double x         = entry.value("x", 0.0);
            double y         = entry.value("y", 0.0);

            auto block = BlockFactory::createBlock(type);
            if (!block){
                std::cerr << "[ProjectSerializer] WARNING: Unknown block type '" << type << "' — skipped.\n";
                continue;
            }

            block->setId(id);
            block->setX(x);
            block->setY(y);


            if (entry.contains("params") && entry["params"].is_object()){
                std::map<std::string, double> paramMap;
                for (const auto& [key, val] : entry["params"].items()){
                    if (val.is_number()){
                        paramMap[key] = val.get<double>();
                    }
                }
                block->setParameters(paramMap);
            }

            blocks.addBlock(std::move(block));
        }


        if (!project.contains("connections") || !project["connections"].is_array()){
            std::cerr << "[ProjectSerializer] ERROR: Missing or invalid 'connections' array.\n";
            return false;
        }

        for (const auto& entry : project["connections"]){
            std::string from = entry["from"].get<std::string>();
            std::string to   = entry["to"].get<std::string>();
            int fromPort     = entry.value("fromPort", 0);
            int toPort       = entry.value("toPort",   0);

            if (!graph.connect(blocks, from, to, fromPort, toPort)){
                std::cerr << "[ProjectSerializer] WARNING: Could not connect '"
                          << from << "' -> '" << to << "'.\n";
            }
        }


        if (project.contains("settings") && project["settings"].is_object()){
            const auto& settings = project["settings"];
            if (settings.contains("startTime")) scheduler.setStartTime(settings["startTime"].get<double>());
            if (settings.contains("endTime"))   scheduler.setEndTime(settings["endTime"].get<double>());
            if (settings.contains("stepSize"))  scheduler.setStepSize(settings["stepSize"].get<double>());
        }

        std::cout << "[ProjectSerializer] Project loaded from: " << filename << "\n";
        return true;
    }

}
