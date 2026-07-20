#pragma once

#include "Block/Block.hpp"

namespace pass::simulink{
    class ClockBlock : public Block{
        private:
            double currentTime = 0.0;
            double stepSize = 1.0;

        public:
            ClockBlock();
            double execute(const std::vector<double>& inputs) override;
            
            void setStepSize(double step);
            void setCurrentTime(double time);
    };
}