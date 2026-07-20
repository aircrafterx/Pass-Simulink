#include <iostream>
#include <memory>

#include "Block/BlockManager.hpp"
#include "Block/ClockBlock.hpp"
#include "Block/SineBlock.hpp"
#include "Block/CosineBlock.hpp"
#include "Block/ScopeBlock.hpp"
#include "Block/AddBlock.hpp"
#include "Block/MultiplyBlock.hpp"
#include "Block/GainBlock.hpp"

#include "Graph/ConnectionManager.hpp"

#include "Engine/GraphExecutionEngine.hpp"

using namespace pass::simulink;

int main(){
    BlockManager blockManager;

    auto clock = std::make_unique<ClockBlock>();
    clock->setId("Clock_1");

    auto sine = std::make_unique<SineBlock>();
    sine->setId("Sine_1");

    auto add = std::make_unique<AddBlock>();
    add->setId("Add_1");

    auto gain = std::make_unique<GainBlock>(2.0);
    gain->setId("Gain_1");

    auto scope = std::make_unique<ScopeBlock>();
    scope->setId("Scope_1");

    blockManager.addBlock(std::move(clock));
    blockManager.addBlock(std::move(sine));
    blockManager.addBlock(std::move(add));
    blockManager.addBlock(std::move(gain));
    blockManager.addBlock(std::move(scope));

    ConnectionManager graph;

    // Clock_1 -> Sine_1
    graph.connect(blockManager, "Clock_1", "Sine_1");
    // Clock_1 -> Add_1
    graph.connect(blockManager, "Clock_1", "Add_1");
    // Sine_1 -> Add_1
    graph.connect(blockManager, "Sine_1", "Add_1");
    // Add_1 -> Gain_1
    graph.connect(blockManager, "Add_1", "Gain_1");
    // Gain_1 -> Scope_1
    graph.connect(blockManager, "Gain_1", "Scope_1");

    std::cout << "\nConnections\n";
    std::cout << "-----------------------------\n";

    for (const auto &connection : graph.getConnections()){
        std::cout << connection.from << " ---> " << connection.to << '\n';
    }

    std::cout << std::endl;

    GraphExecutionEngine engine(blockManager, graph);

    std::cout << "Simulation Start (Running 3 steps)\n";
    std::cout << "=============================\n";

    engine.execute();
    engine.execute();
    engine.execute();

    std::cout << "=============================\n";
    std::cout << "Simulation Finished\n";

    // Verify Scope has the outputs
    const auto *scopePtr = dynamic_cast<const ScopeBlock*>(blockManager.getBlock("Scope_1"));
    if (scopePtr) {
        std::cout << "Scope Recorded Values: [";
        const auto &vals = scopePtr->getValues();
        for (size_t i = 0; i < vals.size(); ++i) {
            std::cout << vals[i] << (i + 1 < vals.size() ? ", " : "");
        }
        std::cout << "]\n";
    }

    return 0;
}