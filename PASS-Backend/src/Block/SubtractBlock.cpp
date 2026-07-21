#include "Block/SubtractBlock.hpp"

namespace pass::simulink{
    SubtractBlock::SubtractBlock(){}

    double SubtractBlock::execute(const std::vector<double>& inputs){
        if (inputs.empty()) return 0.0;
        double result = inputs[0];
        for (size_t i = 1; i < inputs.size(); ++i) {
            result -= inputs[i];
        }
        return result;
    }

    std::string SubtractBlock::getType() const{
        return "Subtract";
    }
}
