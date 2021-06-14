#include <iostream>
#include <map>
#include <string>
#include <random>
#include "../lib/sha256.h"
#include "BlockChain.h"


std::mt19937_64 rng;
std::uniform_int_distribution<int> uni(0, 3);

std::map<int, int> generateTransactions(int MaxVal);

int main()
{
    // Random ledger generation test

    std::list<std::map<int, int>> transactions;


    for (int i = 0; i < 1000; i++) {
        std::map<int, int> temp = generateTransactions(i);
        transactions.push_back(temp);
    }
    BlockChain blockChain;
    blockChain.transactionsToBlocks(transactions);

    std::list<Block> chain = blockChain.getChain();

    for (auto it = chain.begin(); it != chain.end(); it++) {
        it->getContents().dump();
    }

    for (auto person : blockChain.getState()) {
        std::cerr << person.first << ": " << person.second << std::endl;
    }


    return 0;
}

std::map<int, int> generateTransactions(int MaxVal)
{
    std::uniform_int_distribution<int> distro(0, MaxVal);
    int random_bit = uni(rng);
    int random_integer = distro(rng);
    int sign = (random_bit * 2) - 1;
    int amount = random_integer * sign;
    std::map<int, int> vals = {{1, amount},
                               {2, amount * -1}};
    return vals;
}
