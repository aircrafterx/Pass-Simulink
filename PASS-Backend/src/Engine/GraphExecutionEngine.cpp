#include "Engine/GraphExecutionEngine.hpp"

#include <iostream>
#include <vector>

namespace pass::simulink{
    GraphExecutionEngine::GraphExecutionEngine(BlockManager& blocks, const ConnectionManager& graph)
        : blockManager(blocks), graph(graph){

    }

    void GraphExecutionEngine::execute(){
        context.router.clear();

        auto order = TopologicalSorter::sort(blockManager, graph);
        if (order.size() < blockManager.getBlocks().size()) {
            std::cout << "\nCycle detected. Simulation aborted.\n";
            return;
        }

        std::cout << "\n===== EXECUTION =====\n";

        for (const auto &id : order){
            Block* block = blockManager.getBlock(id);

            if (block == nullptr) continue;

            std::vector<double> inputs;
            auto incoming = graph.incoming(id);

            for (const auto &conn : incoming) {
                auto source = conn.from;
                if (context.router.hasSignal(source)) {
                    inputs.push_back(context.router.getSignal(source));
                } else {
                    inputs.push_back(0.0);
                }
            }

            double output = block->execute(inputs);

            context.router.setSignal(id, output);

            std::cout << id << " : inputs=[";
            for (size_t i = 0; i < inputs.size(); ++i) {
                std::cout << inputs[i];
                if (i + 1 < inputs.size()) {
                    std::cout << ", ";
                }
            }
            std::cout << "] output=" << output << std::endl;
        }

        std::cout << "=====================" << std::endl;
    }

}