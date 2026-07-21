#include "Block/MultiplyBlock.hpp"

namespace pass::simulink{
    MultiplyBlock::MultiplyBlock(){}

    double MultiplyBlock::execute(const std::vector<double>& inputs){
        if (inputs.empty()) return 0.0;
        double product = 1.0;
        for (double val : inputs) {
            product *= val;
        }
        return product;
    }

    std::string MultiplyBlock::getType() const{
        return "Multiply";
    }
}
