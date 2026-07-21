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

            // Cached topological order — recomputed only when dirty.
            std::vector<std::string> cachedOrder;
            bool dirty = true;

        public:
            GraphExecutionEngine(BlockManager &blocks, const ConnectionManager &graph);

            // Computes (or reuses) the sorted execution order.
            // Returns false if a cycle is detected, true otherwise.
            bool prepare();

            // Marks the cached order stale (call after adding/removing blocks or connections).
            void invalidate() { dirty = true; }

            // Runs one simulation tick using the cached order.
            // tickIndex and time are embedded in the JSON output for each tick.
            // Call prepare() at least once before the first execute().
            void execute(int tickIndex = 0, double time = 0.0);

            BlockManager& getBlockManager() { return blockManager; }
            const BlockManager& getBlockManager() const { return blockManager; }
            const ConnectionManager& getGraph() const { return graph; }
    };
}