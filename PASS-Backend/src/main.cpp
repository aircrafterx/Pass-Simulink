#include <iostream>

#include "Block/BlockManager.hpp"
#include "Graph/ConnectionManager.hpp"

int main(){
    pass::simulink::BlockManager blockManager;
    pass::simulink::ConnectionManager connectionManager;

    blockManager.addBlock({"Clock_1", "Clock", 100, 100});
    blockManager.addBlock({"Sine_1", "Sine", 300, 100});
    blockManager.addBlock({"Scope_1", "Scope", 500, 100});

    std::string from = "Clock_1", to = "Sine_1";

    if (connectionManager.connect(blockManager, from, to )){
        std::cout << "Clock -> Sine connected" << std::endl;
    }

    if (!connectionManager.connect(blockManager, from, to)){
        std::cout << "Connection failed" << std::endl;
    }

    for (const auto &connection : connectionManager.getConnections()){
        std::cout << connection.from << " -> " << connection.to << std::endl;
    }

    return 0;
}