#include "Block/ClockBlock.hpp"

namespace pass::simulink{
    ClockBlock::ClockBlock(){}

    double ClockBlock::execute(const std::vector<double>&){
        double t = currentTime;
        currentTime += stepSize;
        return t;
    }

    void ClockBlock::setStepSize(double step){
        stepSize = step;
    }

    void ClockBlock::setCurrentTime(double time){
        currentTime = time;
    }
}