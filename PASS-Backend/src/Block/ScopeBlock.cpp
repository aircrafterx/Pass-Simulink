#include "Block/ScopeBlock.hpp"

namespace pass::simulink{
    ScopeBlock::ScopeBlock(){}

    double ScopeBlock::execute(const std::vector<double>& inputs){
        double val = inputs.empty() ? 0.0 : inputs[0];
        values.push_back(val);
        return val;
    }

    std::string ScopeBlock::getType() const{
        return "Scope";
    }

    const std::vector<double>& ScopeBlock::getValues() const{
        return values;
    }

    void ScopeBlock::reset(){
        values.clear();
    }
}