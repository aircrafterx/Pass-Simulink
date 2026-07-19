#include "Engine/ExecutionEngine.hpp"

namespace pass::simulink{
    ExecutionEngine::ExecutionEngine(){
    }

    void ExecutionEngine::step(){
        clock.tick();

        double t = clock.getTime();
        double s = sine.process(t);
        double c = cosine.process(t);

        scope.addSample(t, s, c);
    }

    const ScopeBlock& ExecutionEngine::getScope() const{
        return scope;
    }
}