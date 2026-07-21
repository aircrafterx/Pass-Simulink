#pragma once
#include <memory>
#include <string>
#include "Block/Block.hpp"

namespace pass::simulink {
    class BlockFactory {
    public:
        static std::unique_ptr<Block> createBlock(const std::string& type);
    };
}
