#pragma once

#include "Block/Block.hpp"

namespace pass::simulink{
    class CosineBlock : public Block{
        public:
            CosineBlock();
            double execute(double input) override;
    };
}