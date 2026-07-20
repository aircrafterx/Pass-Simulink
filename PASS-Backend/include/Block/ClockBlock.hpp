#pragma once

#include "Block/Block.hpp"

namespace pass::simulink{
    class ClockBlock : public Block{
        private:
            double currentTime = 0.0;

        public:
            ClockBlock();
            double execute(double input) override;
    };
}