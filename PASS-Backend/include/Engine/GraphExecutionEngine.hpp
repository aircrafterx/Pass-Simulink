#pragma once

#include "Block/BlockManager.hpp"
#include "Graph/ConnectionManager.hpp"
#include "Engine/SignalRouter.hpp"

namespace pass::simulink{
    class GraphExecutionEngine{
        private:
            const BlockManager& blockManager;
            const ConnectionManager& connectionManager;
            SignalRouter router;

        public:
            GraphExecutionEngine(
                const BlockManager &blocks,
                const ConnectionManager &graph);

            void execute();
    };
}