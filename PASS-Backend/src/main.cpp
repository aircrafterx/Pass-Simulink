#include <iostream>

#include "Engine/ExecutionEngine.hpp"

int main(){
    pass::simulink::ExecutionEngine engine;

    for(int i = 0; i < 10; i++) engine.step();

    for(const auto& sample : engine.getScope().getSamples()){
        std::cout << "Time: " << sample.time << ", Sine: " << sample.sine << ", cosine: " << sample.cosine << std::endl;
    }

    return 0;
}