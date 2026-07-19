#pragma once

#include "Block/BlockManager.hpp"
#include "Graph/ConnectionManager.hpp"

namespace pass::simulink{
    class GraphExecutionEngine{
        private:
            const BlockManager &blockManager;
            const ConnectionManager &connectionManager;

        public:
            GraphExecutionEngine(
                const BlockManager &blocks,
                const ConnectionManager &graph);

            void execute() const;
    };
}