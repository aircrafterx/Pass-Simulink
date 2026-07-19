#pragma once

#include "Clock/ClockBlock.hpp"
#include "Sine/SineBlock.hpp"
#include "Cosine/CosineBlock.hpp"
#include "Scope/ScopeBlock.hpp"
#include "Graph/ConnectionManager.hpp"

namespace pass::simulink{
    class ExecutionEngine{
        private:
            ClockBlock clock;
            SineBlock sine;
            CosineBlock cosine;
            ScopeBlock scope;

            ConnectionManager graph;

        public:
            ExecutionEngine();
            void step();
            const ScopeBlock& getScope() const;
    };
}