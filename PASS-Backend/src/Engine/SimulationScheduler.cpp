#include "Engine/SimulationScheduler.hpp"
#include "Block/ClockBlock.hpp"
#include "Graph/TopologicalSorter.hpp"
#include <iostream>

namespace pass::simulink{
    SimulationScheduler::SimulationScheduler(GraphExecutionEngine& engine, double start, double end, double step)
        : engine(engine), startTime(start), endTime(end), stepSize(step){}

    void SimulationScheduler::run(){
        // Pre-run cycle check to prevent looping on invalid graphs
        auto order = TopologicalSorter::sort(engine.getBlockManager(), engine.getGraph());
        if (order.size() < engine.getBlockManager().getBlocks().size()){
            std::cout << "\nCycle detected. Simulation aborted.\n";
            return;
        }

        // Configure all Clock blocks using scheduler settings
        for (const auto& pair : engine.getBlockManager().getBlocks()){
            if (auto* clockBlock = dynamic_cast<ClockBlock*>(pair.second.get())){
                clockBlock->setStepSize(stepSize);
                clockBlock->setCurrentTime(startTime);
            }
        }

        double currentTime = startTime;
        while (currentTime <= endTime + 1e-9){
            std::cout << "\n--- Time Tick: " << currentTime << " ---\n";
            engine.execute();
            currentTime += stepSize;
        }
    }

    double SimulationScheduler::getStartTime() const { return startTime; }
    void SimulationScheduler::setStartTime(double start) { startTime = start; }

    double SimulationScheduler::getEndTime() const { return endTime; }
    void SimulationScheduler::setEndTime(double end) { endTime = end; }

    double SimulationScheduler::getStepSize() const { return stepSize; }
    void SimulationScheduler::setStepSize(double step) { stepSize = step; }
}
