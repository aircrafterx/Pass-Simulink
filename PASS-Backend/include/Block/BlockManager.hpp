#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Block/Block.hpp"

namespace pass::simulink{
    class BlockManager{
        private:
            std::unordered_map<std::string, std::unique_ptr<Block>> blocks;

        public:
            bool addBlock(std::unique_ptr<Block> block);
            bool removeBlock(const std::string& id);
            void clear();

            Block* getBlock(const std::string& id);
            const Block* getBlock(const std::string& id) const;

            const auto& getBlocks() const{
                return blocks;
            }
    };

}