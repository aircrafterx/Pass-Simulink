#include "Block/ClockBlock.hpp"

namespace pass::simulink{
    ClockBlock::ClockBlock(){}

    double ClockBlock::execute(const std::vector<double>&){
        double t = currentTime;
        currentTime += stepSize;
        return t;
    }

    void ClockBlock::setStepSize(double step){
        stepSize = step;
    }

    void ClockBlock::setCurrentTime(double time){
        currentTime = time;
    }

    std::string ClockBlock::getType() const{
        return "Clock";
    }

    std::map<std::string, double> ClockBlock::getParameters() const{
        return { {"stepSize", stepSize} };
    }

    void ClockBlock::setParameters(const std::map<std::string, double>& params){
        auto it = params.find("stepSize");
        if (it != params.end()){
            stepSize = it->second;
        }
    }
}