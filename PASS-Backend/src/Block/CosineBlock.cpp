#include "Block/CosineBlock.hpp"

#include <cmath>

namespace pass::simulink{
    CosineBlock::CosineBlock(){}
    double CosineBlock::execute(double input){
        return std::cos(input);
    }
}