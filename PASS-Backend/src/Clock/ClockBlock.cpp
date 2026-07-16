#include "Clock/ClockBlock.hpp"

namespace pass::simulink{
    ClockBlock::ClockBlock() : CurrentTime(0.0), deltaTime(1.0/60.0) {}
    
    void ClockBlock::tick(){
        CurrentTime += deltaTime;
    }

    double ClockBlock::getTime() const{
        return CurrentTime;
    }
}