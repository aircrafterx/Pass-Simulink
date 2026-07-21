#include "Block/MaxBlock.hpp"

#include <algorithm>

namespace pass::simulink{
    MaxBlock::MaxBlock(){}

    double MaxBlock::execute(const std::vector<double>& inputs){
        if (inputs.empty()) return 0.0;
        double maxVal = inputs[0];
        for (size_t i = 1; i < inputs.size(); ++i) {
            maxVal = std::max(maxVal, inputs[i]);
        }
        return maxVal;
    }

    std::string MaxBlock::getType() const{
        return "Max";
    }
}
