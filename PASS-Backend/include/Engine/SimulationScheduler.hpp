#pragma once

#include "Engine/GraphExecutionEngine.hpp"

namespace pass::simulink{
    class SimulationScheduler{
        private:
            GraphExecutionEngine& engine;
            double startTime = 0.0;
            double endTime = 10.0;
            double stepSize = 1.0;

        public:
            SimulationScheduler(GraphExecutionEngine& engine, double start, double end, double step);

            void run();

            double getStartTime() const;
            void setStartTime(double start);

            double getEndTime() const;
            void setEndTime(double end);

            double getStepSize() const;
            void setStepSize(double step);
    };
}
