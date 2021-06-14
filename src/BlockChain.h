#ifndef BGP_COIN_BLOCKCHAIN_H
#define BGP_COIN_BLOCKCHAIN_H

#include <iostream>
#include <map>
#include <list>
#include "../lib/sha256.h"

class BlockContents
{
public:
    BlockContents(int block_number, std::string parent_hash, int transaction_count,
                  std::list<std::map<int, int>> transactions);

    BlockContents(const BlockContents& contents);

    void dump();

    int getBlockNumber();

    std::string getParentHash();

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

    std::string getHash();

    BlockContents getContents();

private:
    std::string block_hash;
    BlockContents contents;
};

class BlockChain
{
public:
    BlockChain();

    void transactionsToBlocks(std::list<std::map<int, int>> trans);


    std::list<Block> getChain();

private:
    std::list<Block> chain;
    std::map<int, int> state;
};

void updateState(std::map<int, int> &state, std::map<int, int> transaction);

bool validateState(std::map<int, int> state, std::map<int, int> transaction);

Block makeBlock(std::list<std::map<int, int>> transactions, std::list<Block> chain);

void checkBlockHash(Block block);

std::map<int, int> checkBlockValidity(Block block, Block parent, std::map<int, int> state);

#endif //BGP_COIN_BLOCKCHAIN_H
