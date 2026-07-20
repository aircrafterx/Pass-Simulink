#include "Block/ScopeBlock.hpp"

namespace pass::simulink{
    ScopeBlock::ScopeBlock(){}

    double ScopeBlock::execute(const std::vector<double>& inputs){
        double val = inputs.empty() ? 0.0 : inputs[0];
        values.push_back(val);
        return val;
    }

    const std::vector<double> &ScopeBlock::getValues() const{
        return values;
    }
}