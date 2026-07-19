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
        // clock.tick();
        // double t = clock.getTime();

        // double sin = 0.0;
        // double cos = 0.0;

        // bool sendSin = false;
        // bool sendCos = false;

        // for(const auto& connection : graph.getConnections()){
        //     if(connection.from == "Clock" && connection.to == "Sine"){
        //         sin = sine.process(t);
        //         sendSin = true;
        //     }

        //     if(connection.from == "Clock" && connection.to == "Cosine"){
        //         cos = cosine.process(t);
        //         sendCos = true;
        //     }
        // }

        // if (sendSin || sendCos){
        //     scope.addSample(t, sendSin ? sin : 0.0, sendCos ? cos : 0.0);
        // }
    }

    const ScopeBlock& ExecutionEngine::getScope() const{
        return scope;
    }
}