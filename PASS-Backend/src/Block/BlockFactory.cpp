#include "Block/BlockFactory.hpp"
#include "Block/ClockBlock.hpp"
#include "Block/SineBlock.hpp"
#include "Block/CosineBlock.hpp"
#include "Block/ScopeBlock.hpp"
#include "Block/AddBlock.hpp"
#include "Block/MultiplyBlock.hpp"
#include "Block/AverageBlock.hpp"
#include "Block/GainBlock.hpp"
#include "Block/SubtractBlock.hpp"
#include "Block/MinBlock.hpp"
#include "Block/MaxBlock.hpp"

namespace pass::simulink {
    std::unique_ptr<Block> BlockFactory::createBlock(const std::string& type) {
        if (type == "Clock") return std::make_unique<ClockBlock>();
        if (type == "Sine") return std::make_unique<SineBlock>();
        if (type == "Cosine") return std::make_unique<CosineBlock>();
        if (type == "Scope") return std::make_unique<ScopeBlock>();
        if (type == "Add") return std::make_unique<AddBlock>();
        if (type == "Multiply") return std::make_unique<MultiplyBlock>();
        if (type == "Average") return std::make_unique<AverageBlock>();
        if (type == "Gain") return std::make_unique<GainBlock>();
        if (type == "Subtract") return std::make_unique<SubtractBlock>();
        if (type == "Min") return std::make_unique<MinBlock>();
        if (type == "Max") return std::make_unique<MaxBlock>();
        return nullptr;
    }
}
