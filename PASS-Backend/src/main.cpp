#include <iostream>

#include "Block/BlockManager.hpp"

int main(){
    pass::simulink::BlockManager manager;

    manager.addBlock({"Clock_1", "Clock", 100, 100});
    manager.addBlock({"Sine_1", "Sine", 300, 100});
    manager.addBlock({"Cosine_1", "Cosine", 300, 250});
    manager.addBlock({"Scope_1", "Scope", 550, 170});

    manager.moveBlock("Clock_1", 200, 150);

    for (const auto &block : manager.getBlocks()){
        std::cout << block.id << " | " << block.type << " | (" << block.x << ", " << block.y << ")" << std::endl;
    }

    return 0;
}