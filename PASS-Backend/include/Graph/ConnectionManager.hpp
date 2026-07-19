#pragma once 

#include <string>
#include <vector>

#include "Block/BlockManager.hpp"

namespace pass::simulink{
    struct Connection{
        std::string from;
        std::string to;
    };

    class ConnectionManager{
        private:
            std::vector<Connection> connections;

        public:
            bool connect(const BlockManager& blockManager, const std::string& from, const std::string& to);
            const std::vector<Connection>& getConnections() const;
    };
}