#include "Engine/SimulationScheduler.hpp"
#include "Block/ClockBlock.hpp"
#include "Block/ScopeBlock.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include <cmath>

namespace pass::simulink{
    SimulationScheduler::SimulationScheduler(GraphExecutionEngine& engine, double start, double end, double step)
        : engine(engine), startTime(start), endTime(end), stepSize(step){}

    void SimulationScheduler::run(){

        engine.invalidate();
        if (!engine.prepare()){
            nlohmann::json err;
            err["error"] = "Cycle detected — simulation aborted";
            std::cout << err.dump(4) << "\n";
            return;
        }


        for (const auto& pair : engine.getBlockManager().getBlocks()){
            if (auto* clockBlock = dynamic_cast<ClockBlock*>(pair.second.get())){
                clockBlock->setStepSize(stepSize);
                clockBlock->setCurrentTime(startTime);
            }
        }


        for (const auto& pair : engine.getBlockManager().getBlocks()){
            if (auto* scope = dynamic_cast<ScopeBlock*>(pair.second.get())){
                scope->reset();
            }
        }


        int numSteps = static_cast<int>(std::round((endTime - startTime) / stepSize));
        for (int i = 0; i <= numSteps; ++i){
            double currentTime = startTime + i * stepSize;
            engine.execute(i, currentTime);
        }
    }

    double SimulationScheduler::getStartTime() const { return startTime; }
    void SimulationScheduler::setStartTime(double start) { startTime = start; }

    double SimulationScheduler::getEndTime() const { return endTime; }
    void SimulationScheduler::setEndTime(double end) { endTime = end; }

    double SimulationScheduler::getStepSize() const { return stepSize; }
    void SimulationScheduler::setStepSize(double step) { stepSize = step; }
}
