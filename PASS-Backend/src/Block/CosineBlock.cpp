#include "Block/CosineBlock.hpp"

#include <cmath>

namespace pass::simulink{

    CosineBlock::CosineBlock(double amp, double freq, double phase)
        : amplitude(amp), frequency(freq), phaseOffset(phase) {}

    double CosineBlock::execute(const std::vector<double>& inputs){
        double t = inputs.empty() ? 0.0 : inputs[0];
        return amplitude * std::cos(frequency * t + phaseOffset);
    }

    std::string CosineBlock::getType() const{
        return "Cosine";
    }

    std::map<std::string, double> CosineBlock::getParameters() const{
        return {
            {"amplitude",   amplitude},
            {"frequency",   frequency},
            {"phaseOffset", phaseOffset}
        };
    }

    void CosineBlock::setParameters(const std::map<std::string, double>& params){
        if (auto it = params.find("amplitude");   it != params.end()) amplitude   = it->second;
        if (auto it = params.find("frequency");   it != params.end()) frequency   = it->second;
        if (auto it = params.find("phaseOffset"); it != params.end()) phaseOffset = it->second;
    }
}