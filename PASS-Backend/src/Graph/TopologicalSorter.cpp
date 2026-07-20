#include "Graph/TopologicalSorter.hpp"

#include <queue>
#include <unordered_map>

namespace pass::simulink{
    std::vector<std::string> TopologicalSorter::sort(const BlockManager& blocks, const ConnectionManager& graph){
        std::unordered_map<std::string, int> indegree;

        for (const auto& pair : blocks.getBlocks()){
            indegree[pair.first] = 0;
        }

        for (const auto& edge : graph.getConnections()){
            indegree[edge.to]++;
        }

        std::queue<std::string> q;
        for (auto& pair : indegree){
            if (pair.second == 0)
                q.push(pair.first);
        }

        std::vector<std::string> order;
        while (!q.empty()){
            auto current = q.front();
            q.pop();

            order.push_back(current);
            auto edges = graph.outgoing(current);
            for (auto& edge : edges){
                indegree[edge.to]--;

                if (indegree[edge.to] == 0)
                    q.push(edge.to);
            }
        }

        return order;
    }
}