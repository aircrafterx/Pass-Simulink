#include <iostream>
#include <memory>

#include "Block/BlockManager.hpp"
#include "Block/ClockBlock.hpp"
#include "Block/SineBlock.hpp"
#include "Block/CosineBlock.hpp"
#include "Block/ScopeBlock.hpp"

#include "Graph/ConnectionManager.hpp"

#include "Engine/GraphExecutionEngine.hpp"

using namespace pass::simulink;

int main(){
    BlockManager blockManager;

    auto clock = std::make_unique<ClockBlock>();
    clock->setId("Clock_1");

    auto sine = std::make_unique<SineBlock>();
    sine->setId("Sine_1");

    auto cosine = std::make_unique<CosineBlock>();
    cosine->setId("Cosine_1");

    auto scope = std::make_unique<ScopeBlock>();
    scope->setId("Scope_1");

    blockManager.addBlock(std::move(clock));
    blockManager.addBlock(std::move(sine));
    blockManager.addBlock(std::move(cosine));
    blockManager.addBlock(std::move(scope));

    ConnectionManager graph;

    graph.connect(blockManager, "Clock_1", "Sine_1");
    graph.connect(blockManager, "Clock_1", "Cosine_1");
    graph.connect(blockManager, "Sine_1", "Scope_1");
    graph.connect(blockManager, "Cosine_1", "Scope_1");

    std::cout << "\nConnections\n";
    std::cout << "-----------------------------\n";

    for (const auto &connection : graph.getConnections()){
        std::cout << connection.from << " ---> " << connection.to << '\n';
    }

    std::cout << std::endl;

    GraphExecutionEngine engine(blockManager, graph);

    std::cout << "Simulation Start\n";
    std::cout << "=============================\n";

    engine.execute();

    std::cout << "=============================\n";
    std::cout << "Simulation Finished\n";

    return 0;
}