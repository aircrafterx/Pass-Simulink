#include "Block/CosineBlock.hpp"

#include <cmath>

namespace pass::simulink{
    CosineBlock::CosineBlock(){}
    double CosineBlock::execute(const std::vector<double>& inputs){
        double val = inputs.empty() ? 0.0 : inputs[0];
        return std::cos(val);
    }
}