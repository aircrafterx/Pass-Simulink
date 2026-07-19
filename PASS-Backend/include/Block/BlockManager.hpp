#pragma once

#include <vector>
#include <string>

#include "Block/Block.hpp"

namespace pass::simulink{
    class BlockManager{
        private:
            std::vector<Block> blocks;

        public:
            void addBlock(const Block& block);
            void moveBlock(const std::string& id, float x, float y);
            Block* getBlock(const std::string& id);
            const Block *getBlock(const std::string& id) const;
            const std::vector<Block> &getBlocks() const;
    };
}