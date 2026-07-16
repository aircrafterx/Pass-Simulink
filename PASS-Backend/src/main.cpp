#include <iostream>

#include "Clock/ClockBlock.hpp"
#include "Sine/SineBlock.hpp"

int main(){
    pass::simulink::ClockBlock clock;
    pass::simulink::SineBlock sine;

    for(int i = 0; i < 10; i++){
        clock.tick();

        double t = clock.getTime();
        double v = sine.process(t);

        std::cout << "t = " << t << ", sin(t) = " << v << std::endl;
    }

    return 0;
}