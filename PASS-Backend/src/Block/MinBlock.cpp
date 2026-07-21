#include "Block/MinBlock.hpp"

#include <algorithm>

namespace pass::simulink{
    MinBlock::MinBlock(){}

    double MinBlock::execute(const std::vector<double>& inputs){
        if (inputs.empty()) return 0.0;
        double minVal = inputs[0];
        for (size_t i = 1; i < inputs.size(); ++i) {
            minVal = std::min(minVal, inputs[i]);
        }
        return minVal;
    }

    std::string MinBlock::getType() const{
        return "Min";
    }
}
