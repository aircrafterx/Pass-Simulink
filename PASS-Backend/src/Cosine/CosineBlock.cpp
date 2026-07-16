#include "Cosine/CosineBlock.hpp"

#include <cmath>

namespace pass::simulink{
    double CosineBlock::process(double time) const{
        return std::cos(time);
    }
}