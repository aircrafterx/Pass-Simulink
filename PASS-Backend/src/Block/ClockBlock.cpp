#include "Block/ClockBlock.hpp"

namespace pass::simulink{
    ClockBlock::ClockBlock(){}

    double ClockBlock::execute(const std::vector<double>&){
        currentTime += 1.0;
        return currentTime;
    }
}