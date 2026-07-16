#include "Sine/SineBlock.hpp"

#include <cmath>

namespace pass::simulink {
    double SineBlock::process(double time) const{
        return std::sin(time);
    }
}