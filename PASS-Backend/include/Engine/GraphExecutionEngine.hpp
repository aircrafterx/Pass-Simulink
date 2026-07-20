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

            BlockManager& getBlockManager() { return blockManager; }
            const BlockManager& getBlockManager() const { return blockManager; }
            const ConnectionManager& getGraph() const { return graph; }
    };
}