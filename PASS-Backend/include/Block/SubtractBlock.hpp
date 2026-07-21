#pragma once

#include "Block/Block.hpp"

namespace pass::simulink{
    class SubtractBlock : public Block{
        public:
            SubtractBlock();
            double execute(const std::vector<double>& inputs) override;
            std::string getType() const override;
    };
}
