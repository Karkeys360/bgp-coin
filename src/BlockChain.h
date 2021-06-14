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

void updateState(std::map<int,int> state, std::map<int,int> transaction){
    for (auto & it : transaction) {
        auto keyValPair = state.find(it.first);
        if(keyValPair!= state.end()) {
            keyValPair->second += it.second;
        }else{
            state.insert({it.first,it.second});
        }
    }
}
bool validateState(std::map<int,int> state, std::map<int,int> transaction){
    bool returner = true;
    int total = 0;
    for(auto & it : transaction){
        total += it.second;
        auto keyValPair = state.find(it.first);
        if(keyValPair!= state.end() && keyValPair->second < it.second * -1) {
            returner = false;
        }
    }
    if(total != 0){
        returner = false;
    }
    return returner;
}

#endif //BGP_COIN_BLOCKCHAIN_H
