#pragma once

#include <vector>
#include <string>

#include "Block/BlockManager.hpp"
#include "Graph/ConnectionManager.hpp"

namespace pass::simulink{
    class TopologicalSorter{
        public:
            static std::vector<std::string>
            sort(const BlockManager& blocks, const ConnectionManager& graph);
    };

}