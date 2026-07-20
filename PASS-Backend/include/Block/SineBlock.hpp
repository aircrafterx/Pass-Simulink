#pragma once

#include "Block/Block.hpp"

namespace pass::simulink{
    class SineBlock : public Block{
        public:
            SineBlock();
            double execute(const std::vector<double>& inputs) override;
    };
}