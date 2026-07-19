#include "Engine/GraphExecutionEngine.hpp"

#include <iostream>

namespace pass::simulink{
    GraphExecutionEngine::GraphExecutionEngine(const BlockManager &blocks, const ConnectionManager &graph) : blockManager(blocks), connectionManager(graph){
    }

    void GraphExecutionEngine::execute() const{
        std::cout << "========== EXECUTION GRAPH ==========\n";
        for (const auto& connection : connectionManager.getConnections()){
            const Block* from = blockManager.getBlock(connection.from);
            const Block* to = blockManager.getBlock(connection.to);

            if (from && to){
                std::cout << from->type << " (" << from->id << ") -> " << to->type << " (" << to->id << ")" << std::endl;
            }
        }

        std::cout << "=====================================\n";
    }

}