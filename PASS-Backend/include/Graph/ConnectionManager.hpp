#pragma once

#include <string>
#include <vector>

#include "Graph/Connection.hpp"
#include "Block/BlockManager.hpp"

namespace pass::simulink{
    class ConnectionManager{
    private:
        std::vector<Connection> connections;

    public:
        bool connect(const BlockManager& blocks, const std::string& from, const std::string& to);
        bool disconnect(const std::string& from, const std::string& to);
        bool isConnected(const std::string& from, const std::string& to) const;
        std::vector<Connection> outgoing(const std::string& blockId) const;
        std::vector<Connection> incoming(const std::string& blockId) const;
        const std::vector<Connection>& getConnections() const;
    };

}