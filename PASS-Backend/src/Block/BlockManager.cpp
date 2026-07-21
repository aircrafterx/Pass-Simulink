#include "Block/BlockManager.hpp"

namespace pass::simulink{
    bool BlockManager::addBlock(std::unique_ptr<Block> block){
        if (block == nullptr)
            return false;

        std::string id = block->getId();

        if (blocks.contains(id))
            return false;

        blocks[id] = std::move(block);

        return true;
    }

    bool BlockManager::removeBlock(const std::string& id){
        return blocks.erase(id) > 0;
    }

    void BlockManager::clear(){
        blocks.clear();
    }

    Block *BlockManager::getBlock(const std::string &id){
        auto it = blocks.find(id);

        if (it == blocks.end())
            return nullptr;

        return it->second.get();
    }

    const Block *BlockManager::getBlock(const std::string &id) const{
        auto it = blocks.find(id);

        if (it == blocks.end())
            return nullptr;

        return it->second.get();
    }
}