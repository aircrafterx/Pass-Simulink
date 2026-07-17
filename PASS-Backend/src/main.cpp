#include <iostream>

#include "Clock/ClockBlock.hpp"
#include "Sine/SineBlock.hpp"
#include "Cosine/CosineBlock.hpp"
#include "Scope/ScopeBlock.hpp"

int main(){
    pass::simulink::ClockBlock clock;
    pass::simulink::SineBlock sine;
    pass::simulink::CosineBlock cosine;
    pass::simulink::ScopeBlock scope;

    for(int i = 0; i < 10; i++){
        clock.tick();

        double t = clock.getTime();
        double s = sine.process(t);
        double c = cosine.process(t);

        scope.addSample(t, s, c);
    }

    for(const auto& sample : scope.getSamples()){
        std::cout << "Time: " << sample.time << " Sine: " << sample.sine << " Cosine: " << sample.cosine << std::endl;
    }

    return 0;
}