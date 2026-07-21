#pragma once

#include <vector>

#include "Block/Block.hpp"

namespace pass::simulink{
    class ScopeBlock : public Block{
        private:
            std::vector<double> values;

        public:
            ScopeBlock();
            double execute(const std::vector<double>& inputs) override;
            std::string getType() const override;
            const std::vector<double>& getValues() const;
            void reset();
    };
}