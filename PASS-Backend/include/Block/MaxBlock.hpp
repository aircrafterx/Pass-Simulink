#pragma once

#include "Block/Block.hpp"

namespace pass::simulink{
    class MaxBlock : public Block{
        public:
            MaxBlock();
            double execute(const std::vector<double>& inputs) override;
    };
}
