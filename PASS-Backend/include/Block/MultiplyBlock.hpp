#pragma once

#include "Block/Block.hpp"

namespace pass::simulink{
    class MultiplyBlock : public Block{
        public:
            MultiplyBlock();
            double execute(const std::vector<double>& inputs) override;
    };
}
