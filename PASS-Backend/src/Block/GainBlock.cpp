#include "Block/GainBlock.hpp"

namespace pass::simulink{
    GainBlock::GainBlock(){}
    GainBlock::GainBlock(double gainValue) : gain(gainValue){}

    void GainBlock::setGain(double gainValue){
        gain = gainValue;
    }

    double GainBlock::getGain() const{
        return gain;
    }

    double GainBlock::execute(const std::vector<double>& inputs){
        double val = inputs.empty() ? 0.0 : inputs[0];
        return val * gain;
    }
}
