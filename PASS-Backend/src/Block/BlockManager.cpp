#include "Block/BlockManager.hpp"

namespace pass::simulink{
    void BlockManager::addBlock(const Block &block){
        blocks.push_back(block);
    }

    void BlockManager::moveBlock(const std::string &id, float x, float y){
        for (auto &block : blocks){
            if (block.id == id){
                block.x = x;
                block.y = y;
                return;
            }
        }
    }

    Block *BlockManager::getBlock(const std::string &id){
        for (auto &block : blocks){
            if (block.id == id){
                return &block;
            }
        }
        return nullptr;
    }

    const Block *BlockManager::getBlock(const std::string &id) const{
        for (const auto &block : blocks){
            if (block.id == id){
                return &block;
            }
        }

        return nullptr;
    }

    const std::vector<Block> &BlockManager::getBlocks() const{
        return blocks;
    }

}