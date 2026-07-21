#pragma once

#include <string>
#include "Block/BlockManager.hpp"
#include "Graph/ConnectionManager.hpp"
#include "Engine/SimulationScheduler.hpp"

namespace pass::simulink{
    class ProjectSerializer{
        public:
            static bool saveToFile(const std::string& filename,
                                   const BlockManager& blocks,
                                   const ConnectionManager& graph,
                                   const SimulationScheduler& scheduler);

            static bool loadFromFile(const std::string& filename,
                                     BlockManager& blocks,
                                     ConnectionManager& graph,
                                     SimulationScheduler& scheduler);
    };
}
