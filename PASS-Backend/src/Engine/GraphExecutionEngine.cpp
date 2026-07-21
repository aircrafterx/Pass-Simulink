#include "Engine/GraphExecutionEngine.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace pass::simulink{
    GraphExecutionEngine::GraphExecutionEngine(BlockManager& blocks, const ConnectionManager& graph)
        : blockManager(blocks), graph(graph){

    }





    bool GraphExecutionEngine::prepare(){
        cachedOrder = TopologicalSorter::sort(blockManager, graph);
        dirty = false;
        return cachedOrder.size() == blockManager.getBlocks().size();
    }




    void GraphExecutionEngine::execute(int tickIndex, double time){

        if (dirty){
            if (!prepare()){
                json err;
                err["error"] = "Cycle detected — simulation aborted";
                std::cout << err.dump(4) << "\n";
                return;
            }
        }

        context.router.clear();

        json tickResult;
        tickResult["tick"]      = tickIndex;
        tickResult["time"]      = time;
        tickResult["execution"] = json::array();

        for (const auto& id : cachedOrder){
            Block* block = blockManager.getBlock(id);
            if (block == nullptr) continue;


            auto incoming = graph.incoming(id);
            std::sort(incoming.begin(), incoming.end(),
                      [](const Connection& a, const Connection& b){
                          return a.toPort < b.toPort;
                      });

            int maxPort = incoming.empty() ? -1 : incoming.back().toPort;
            std::vector<double> inputs(static_cast<size_t>(maxPort + 1), 0.0);

            for (const auto& conn : incoming){
                if (context.router.hasSignal(conn.from)){
                    inputs[static_cast<size_t>(conn.toPort)] =
                        context.router.getSignal(conn.from);
                }
            }

            double output = block->execute(inputs);
            context.router.setSignal(id, output);

            json blockResult;
            blockResult["id"]     = id;
            blockResult["type"]   = block->getType();
            blockResult["inputs"] = inputs;
            blockResult["output"] = output;
            tickResult["execution"].push_back(blockResult);
        }

        std::cout << tickResult.dump(4) << "\n";
    }

}