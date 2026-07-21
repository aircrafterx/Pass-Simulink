#pragma once

#include "Block/Block.hpp"

namespace pass::simulink{
    class AverageBlock : public Block{
        public:
            AverageBlock();
            double execute(const std::vector<double>& inputs) override;
            std::string getType() const override;
    };
}
