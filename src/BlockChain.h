#ifndef BGP_COIN_BLOCKCHAIN_H
#define BGP_COIN_BLOCKCHAIN_H

#include <map>
#include <list>
#include "../lib/sha256.h"

class BlockContents
{
public:
    BlockContents(int block_number, std::string parent_hash, int transaction_count,
                  std::list<std::map<int, int>> transactions);
    BlockContents(const BlockContents& contents);
    std::string hash_contents();
private:
    int block_number;
    std::string parent_hash;
    int transaction_count;
    std::list<std::map<int, int>> transactions;
};

class Block
{
public:
    Block(std::string block_hash, BlockContents contents);
private:
    std::string block_hash;
    BlockContents contents;
};

class BlockChain
{
    BlockChain();

private:
    std::list<Block> chain;
};


#endif //BGP_COIN_BLOCKCHAIN_H
