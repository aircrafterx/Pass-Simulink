#include "Engine/GraphExecutionEngine.hpp"

#include <iostream>

namespace pass::simulink{
    GraphExecutionEngine::GraphExecutionEngine(const BlockManager &blocks, const ConnectionManager &graph) : blockManager(blocks), connectionManager(graph){
    }

    void GraphExecutionEngine::execute(){
        std::cout << "========== Dynamic Signal Routing ==========\n";
        for (const auto &connection : connectionManager.getConnections()){
            const Block* from = blockManager.getBlock(connection.from);
            const Block* to = blockManager.getBlock(connection.to);

            if (!from || !to) continue;
            std::cout << from->id << " ---> " << to->id << std::endl;

            double signal = static_cast<double>(from->id.length());
            router.setSignal(from->id, signal);

            if (router.hasSignal(from->id)){
                double received = router.getSignal(from->id);
                std::cout << "Signal " << received << " routed to " << to->id << std::endl;
            }
        }

        std::cout << "=====================================\n";
    }

}