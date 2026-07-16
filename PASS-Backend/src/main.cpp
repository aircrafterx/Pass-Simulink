#include <iostream>

#include "Clock/ClockBlock.hpp"
#include "Sine/SineBlock.hpp"
#include "Cosine/CosineBlock.hpp"

int main(){
    pass::simulink::ClockBlock clock;
    pass::simulink::SineBlock sine;
    pass::simulink::CosineBlock cosine;

    for(int i = 0; i < 10; i++){
        clock.tick();

        double t = clock.getTime();
        double s = sine.process(t);
        double c = cosine.process(t);

        std::cout << "t = " << t << ", sin(t) = " << s << ", cos(t) = " << c << std::endl;
    }

    return 0;
}