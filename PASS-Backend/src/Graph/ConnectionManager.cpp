#include "Graph/ConnectionManager.hpp"

#include <algorithm>

namespace pass::simulink{
    bool ConnectionManager::connect(const BlockManager& blocks,
                                    const std::string& from, const std::string& to,
                                    int fromPort, int toPort){
        if (blocks.getBlock(from) == nullptr)
            return false;

        if (blocks.getBlock(to) == nullptr)
            return false;

        if (isConnected(from, to, fromPort, toPort))
            return false;

        connections.push_back({from, to, fromPort, toPort});
        return true;
    }

    bool ConnectionManager::disconnect(const std::string& from, const std::string& to,
                                       int fromPort, int toPort){
        auto it = std::remove_if(connections.begin(), connections.end(), [&](const Connection& c){
                return c.from == from && c.to == to
                    && c.fromPort == fromPort && c.toPort == toPort;
        });

        if (it == connections.end())
            return false;

        connections.erase(it, connections.end());
        return true;
    }

    bool ConnectionManager::isConnected(const std::string& from, const std::string& to,
                                        int fromPort, int toPort) const{
        for (const auto& c : connections){
            if (c.from == from && c.to == to
                && c.fromPort == fromPort && c.toPort == toPort)
                return true;
        }

        return false;
    }

    std::vector<Connection> ConnectionManager::outgoing(const std::string& blockId) const{
        std::vector<Connection> result;

        for (const auto& c : connections){
            if (c.from == blockId)
                result.push_back(c);
        }

        return result;
    }

    std::vector<Connection> ConnectionManager::incoming(const std::string& blockId) const{
        std::vector<Connection> result;
        for (const auto& c : connections){
            if (c.to == blockId)
                result.push_back(c);
        }

        return result;
    }

    const std::vector<Connection>& ConnectionManager::getConnections() const{
        return connections;
    }

    void ConnectionManager::clear(){
        connections.clear();
    }
}