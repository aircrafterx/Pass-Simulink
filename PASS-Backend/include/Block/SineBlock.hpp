#pragma once

#include "Block/Block.hpp"

namespace pass::simulink{
    class SineBlock : public Block{
        private:
            double amplitude    = 1.0;
            double frequency    = 1.0;
            double phaseOffset  = 0.0;

        public:
            SineBlock() = default;
            explicit SineBlock(double amp, double freq = 1.0, double phase = 0.0);

            double execute(const std::vector<double>& inputs) override;
            std::string getType() const override;

            std::map<std::string, double> getParameters() const override;
            void setParameters(const std::map<std::string, double>& params) override;
    };
}