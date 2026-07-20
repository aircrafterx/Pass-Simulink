#pragma once

#include <vector>

#include "Block/Block.hpp"

namespace pass::simulink{
    class ScopeBlock : public Block{
        private:
            std::vector<double> values;

        public:
            ScopeBlock();
            double execute(double input) override;
            const std::vector<double> &getValues() const;
    };
}