#include "Block/ScopeBlock.hpp"

namespace pass::simulink{
    ScopeBlock::ScopeBlock(){}

    double ScopeBlock::execute(double input){
        values.push_back(input);
        return input;
    }

    const std::vector<double> &ScopeBlock::getValues() const{
        return values;
    }
}