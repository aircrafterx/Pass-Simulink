#include "Block/AddBlock.hpp"

#include <numeric>

namespace pass::simulink{
    AddBlock::AddBlock(){}

    double AddBlock::execute(const std::vector<double>& inputs){
        double sum = 0.0;
        for (double val : inputs) {
            sum += val;
        }
        return sum;
    }
}
