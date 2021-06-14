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

//    void transactionsToBlocks(std::list<std::map<int, int>> trans);


    std::list<Block> getChain();

private:
    std::list<Block> chain;
    std::map<int, int> state;
};

//void updateState(std::map<int, int> state, std::map<int, int> transaction)
//{
//    for (auto& it : transaction) {
//        auto keyValPair = state.find(it.first);
//        if (keyValPair != state.end()) {
//            keyValPair->second += it.second;
//        } else {
//            state.insert({it.first, it.second});
//        }
//    }
//}
//
//bool validateState(std::map<int, int> state, std::map<int, int> transaction)
//{
//    bool returner = true;
//    int total = 0;
//    for (auto& it : transaction) {
//        total += it.second;
//        auto keyValPair = state.find(it.first);
//        if (keyValPair != state.end() && keyValPair->second < it.second * -1) {
//            returner = false;
//        }
//    }
//    if (total != 0) {
//        returner = false;
//    }
//    return returner;
//}
//
//Block makeBlock(std::list<std::map<int, int>> transactions, std::list<Block> chain)
//{
//    Block parent_block = *chain.rbegin();
//    std::string parent_hash = parent_block.getHash();
//    int block_number = parent_block.getContents().getBlockNumber() + 1;
//    int transaction_count = transactions.size();
//    BlockContents contents(block_number, parent_hash, transaction_count, transactions);
//    std::string block_hash = contents.hash_contents();
//
//    Block output(block_hash, contents);
//    return output;
//}

#endif //BGP_COIN_BLOCKCHAIN_H
