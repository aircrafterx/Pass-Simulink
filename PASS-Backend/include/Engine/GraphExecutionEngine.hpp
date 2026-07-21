#pragma once

#include <vector>
#include <string>

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


            std::vector<std::string> cachedOrder;
            bool dirty = true;

        public:
            GraphExecutionEngine(BlockManager &blocks, const ConnectionManager &graph);



            bool prepare();


            void invalidate() { dirty = true; }




            void execute(int tickIndex = 0, double time = 0.0);

            BlockManager& getBlockManager() { return blockManager; }
            const BlockManager& getBlockManager() const { return blockManager; }
            const ConnectionManager& getGraph() const { return graph; }
    };
}