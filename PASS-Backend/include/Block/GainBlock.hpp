#pragma once

#include "Block/Block.hpp"

namespace pass::simulink{
    class GainBlock : public Block{
        private:
            double gain = 1.0;
        public:
            GainBlock();
            explicit GainBlock(double gainValue);

            void setGain(double gainValue);
            double getGain() const;

            double execute(const std::vector<double>& inputs) override;
            std::string getType() const override;

            std::map<std::string, double> getParameters() const override;
            void setParameters(const std::map<std::string, double>& params) override;
    };
}
