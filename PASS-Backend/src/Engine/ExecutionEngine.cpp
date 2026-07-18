#include "Engine/ExecutionEngine.hpp"

namespace pass::simulink{
    void ExecutionEngine::step(){
        clock.tick();
        double t = clock.getTime();
        double sin = sine.process(t);
        double cos = cosine.process(t);
        scope.addSample(t, sin, cos);
    }

    const ScopeBlock& ExecutionEngine::getScope() const{
        return scope;
    }
}