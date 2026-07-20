#include "Block/SineBlock.hpp"

#include <cmath>

namespace pass::simulink{
    SineBlock::SineBlock(){}
    double SineBlock::execute(double input){
        return std::sin(input);
    }
}