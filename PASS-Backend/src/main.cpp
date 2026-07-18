#include <iostream>

#include "Graph/ConnectionManager.hpp"

int main(){
    pass::simulink::ConnectionManager graph;

    graph.connect("Clock", "Sine");
    graph.connect("Clock", "Cosine");
    graph.connect("Sine", "Scope");
    graph.connect("Cosine", "Scope");

    for(const auto& c : graph.getConnections()){
        std::cout << c.from << " -> " << c.to << std::endl;
    }

    return 0;
}