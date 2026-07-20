#pragma once

#include "Block/Block.hpp"

namespace pass::simulink{
    class MinBlock : public Block{
        public:
            MinBlock();
            double execute(const std::vector<double>& inputs) override;
    };
}
