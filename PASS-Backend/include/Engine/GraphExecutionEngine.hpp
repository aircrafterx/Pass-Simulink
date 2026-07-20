#pragma once

#include "Block/BlockManager.hpp"
#include "Graph/ConnectionManager.hpp"
#include "Graph/TopologicalSorter.hpp"
#include "Engine/ExecutionContext.hpp"

namespace pass::simulink{
    class GraphExecutionEngine{
        private:
            BlockManager& blockManager;
            const ConnectionManager& graph;
            ExecutionContext context;

        public:
            GraphExecutionEngine(BlockManager &blocks, const ConnectionManager &graph);
            void execute();
    };
}