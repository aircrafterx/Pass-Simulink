#include "Graph/ConnectionManager.hpp"

namespace pass::simulink{
    void ConnectionManager::connect(const std::string& from, const std::string& to){
        connections.push_back({from, to});
    }

    const std::vector<Connection>& ConnectionManager::getConnections() const
    {
        return connections;
    }
}