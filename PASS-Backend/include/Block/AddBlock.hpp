#pragma once

#include "Block/Block.hpp"

namespace pass::simulink{
    class AddBlock : public Block{
        public:
            AddBlock();
            double execute(const std::vector<double>& inputs) override;
    };
}
