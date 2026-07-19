#include "Block/BlockManager.hpp"
#include "Graph/ConnectionManager.hpp"
#include "Engine/GraphExecutionEngine.hpp"

int main(){
    pass::simulink::BlockManager blocks;
    pass::simulink::ConnectionManager graph;

    blocks.addBlock({"Clock_1", "Clock", 100, 100});
    blocks.addBlock({"Sine_1", "Sine", 300, 100});
    blocks.addBlock({"Cosine_1", "Cosine", 300, 250});
    blocks.addBlock({"Scope_1", "Scope", 500, 150});

    graph.connect(blocks, "Clock_1", "Sine_1");
    graph.connect(blocks, "Clock_1", "Cosine_1");
    graph.connect(blocks, "Sine_1", "Scope_1");
    graph.connect(blocks, "Cosine_1", "Scope_1");

    pass::simulink::GraphExecutionEngine engine(blocks, graph);

    engine.execute();

    return 0;
}