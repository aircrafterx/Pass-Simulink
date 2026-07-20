#include "Block/AverageBlock.hpp"

namespace pass::simulink{
    AverageBlock::AverageBlock(){}

    double AverageBlock::execute(const std::vector<double>& inputs){
        if (inputs.empty()) return 0.0;
        double sum = 0.0;
        for (double val : inputs) {
            sum += val;
        }
        return sum / static_cast<double>(inputs.size());
    }
}
