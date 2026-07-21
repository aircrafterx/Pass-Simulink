#include "Block/SineBlock.hpp"

#include <cmath>

namespace pass::simulink{

    SineBlock::SineBlock(double amp, double freq, double phase)
        : amplitude(amp), frequency(freq), phaseOffset(phase) {}

    double SineBlock::execute(const std::vector<double>& inputs){
        double t = inputs.empty() ? 0.0 : inputs[0];
        return amplitude * std::sin(frequency * t + phaseOffset);
    }

    std::string SineBlock::getType() const{
        return "Sine";
    }

    std::map<std::string, double> SineBlock::getParameters() const{
        return {
            {"amplitude",   amplitude},
            {"frequency",   frequency},
            {"phaseOffset", phaseOffset}
        };
    }

    void SineBlock::setParameters(const std::map<std::string, double>& params){
        if (auto it = params.find("amplitude");   it != params.end()) amplitude   = it->second;
        if (auto it = params.find("frequency");   it != params.end()) frequency   = it->second;
        if (auto it = params.find("phaseOffset"); it != params.end()) phaseOffset = it->second;
    }
}