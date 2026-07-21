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
            std::string getType() const override;

            void setStepSize(double step);
            void setCurrentTime(double time);

            std::map<std::string, double> getParameters() const override;
            void setParameters(const std::map<std::string, double>& params) override;
    };
}