#include "Block/SineBlock.hpp"

#include <cmath>

namespace pass::simulink{
    SineBlock::SineBlock(){}
    double SineBlock::execute(const std::vector<double>& inputs){
        double val = inputs.empty() ? 0.0 : inputs[0];
        return std::sin(val);
    }
}