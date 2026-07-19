#include "Graph/ConnectionManager.hpp"

namespace pass::simulink{
    bool ConnectionManager::connect(const BlockManager &blockManager, const std::string &from, const std::string &to){
        if (blockManager.getBlock(from) == nullptr)
            return false;

        if (blockManager.getBlock(to) == nullptr)
            return false;

        connections.push_back({from, to});
        return true;
    }

    const std::vector<Connection>& ConnectionManager::getConnections() const{
        return connections;
    }
}