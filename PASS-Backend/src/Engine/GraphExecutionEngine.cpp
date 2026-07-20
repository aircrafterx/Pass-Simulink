#include "Engine/GraphExecutionEngine.hpp"

#include <iostream>

namespace pass::simulink{
    GraphExecutionEngine::GraphExecutionEngine(BlockManager& blocks, const ConnectionManager& graph)
        : blockManager(blocks), graph(graph){

    }

    void GraphExecutionEngine::execute(){
        context.router.clear();

        auto order = TopologicalSorter::sort(blockManager, graph);
        std::cout << "\n===== EXECUTION =====\n";

        for (const auto &id : order){
            Block* block = blockManager.getBlock(id);

            if (block == nullptr) continue;

            double input = 0.0;
            auto incoming = graph.incoming(id);

            if (!incoming.empty()){
                auto source = incoming.front().from;

                if (context.router.hasSignal(source)) {
                    input = context.router.getSignal(source);
                }
            }

            double output = block->execute(input);

            context.router.setSignal(id, output);

            std::cout << id << " : input=" << input << " output=" << output << std::endl;
        }

        std::cout << "=====================" << std::endl;
    }

}