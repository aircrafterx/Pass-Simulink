#include "Scope/ScopeBlock.hpp"

namespace pass::simulink{
    void ScopeBlock::addSample(double time, double sine, double cosine){
        samples.push_back({time, sine, cosine});
    }

    const std::vector<ScopeSample>& ScopeBlock::getSamples() const{
        return samples;
    }
}