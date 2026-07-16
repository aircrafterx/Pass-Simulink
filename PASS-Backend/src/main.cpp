#include <iostream>

#include "Clock/ClockBlock.hpp"

int main(){
    backend::ClockBlock clock;

    for(int i = 0; i < 10; i++){
        clock.tick();
        std::cout << "t = " << clock.getTime() << std::endl;
    }
    
    return 0;
}