#include "BlockChain.h"

BlockContents::BlockContents(int block_number, std::string parent_hash, int transaction_count,
                             std::list<std::map<int, int>> transactions)
{
    this->block_number = block_number;
    this->parent_hash = parent_hash;
    this->transaction_count = transaction_count;
    this->transactions = transactions;
}

std::string BlockContents::hash_contents()
{
    std::string hash_transactions;
    std::string hash_contents;

    std::string to_hash = "";
    for (auto it = transactions.begin(); it != transactions.end(); it++) {
        for (auto map_it = it->begin(); map_it != it->end(); map_it++) {
            to_hash += std::to_string(map_it->first) + "." + std::to_string(map_it->second);
        }
    }

    picosha2::hash256_hex_string(to_hash, hash_transactions);

    to_hash = std::to_string(block_number) + "." + parent_hash + "." + std::to_string(transaction_count) + "." +
              hash_transactions;

    picosha2::hash256_hex_string(to_hash, hash_contents);

    return hash_contents;
}

BlockContents::BlockContents(const BlockContents& contents) : transactions(contents.transactions)
{
    this->block_number = contents.block_number;
    this->parent_hash = contents.parent_hash;
    this->transaction_count = contents.transaction_count;
}

int BlockContents::getBlockNumber()
{
    return this->block_number;
}

void BlockContents::dump()
{
    std::cerr << "Block Number: " << block_number << std::endl;
    std::cerr << "Parent Hash: " << parent_hash << std::endl;
    std::cerr << "Transaction Count: " << transaction_count << std::endl;
    std::cerr << "Transactions: " << std::endl;

    for (auto transaction : transactions) {
        std::cerr << "New Transaction:" << std::endl;
        for (auto change : transaction) {
            std::cerr << change.first << ": " << change.second << std::endl;
        }
        std::cerr << std::endl;
    }
}

std::string BlockContents::getParentHash()
{
    return this->parent_hash;
}

Block::Block(std::string new_hash, BlockContents new_contents) : contents(new_contents)
{
    this->block_hash = new_hash;
}

std::string Block::getHash()
{
    return this->block_hash;
}

BlockContents Block::getContents()
{
    return this->contents;
}

BlockChain::BlockChain()
{
    std::map<int, int> start_state = {{1, 100000000},
                                      {2, 100000000}};
    this -> state = start_state;
    std::list<std::map<int, int>> genesis_block_transactions;
    genesis_block_transactions.push_back(start_state);

    BlockContents genesis_block_contents(0, "", 1, genesis_block_transactions);
    std::string genesis_hash = genesis_block_contents.hash_contents();

    Block genesis_block(genesis_hash, genesis_block_contents);

    this->chain.push_back(genesis_block);

}


void BlockChain::transactionsToBlocks(std::list<std::map<int, int>> trans)
{
    std::map<int, int> currentState = state;
    int transactionLim = 3; // transactions per block
    int counter = 0;
    std::list<std::map<int, int>> transList;
    for (auto it = trans.begin(); it != trans.end(); it++) {
        if (validateState(currentState, *it)) {
            updateState(currentState, *it);
            transList.push_back(*it);
            counter++;
        }
        if (counter == transactionLim || std::next(it) == trans.end()) {
            counter = 0;
            Block temp = makeBlock(transList, chain);
            chain.push_back(temp);
            transList.clear();
        }

    }

    state = currentState;
}

void updateState(std::map<int, int> &state, std::map<int, int> transaction)
{
    for (auto& it : transaction) {
        auto keyValPair = state.find(it.first);
        if (keyValPair != state.end()) {
            keyValPair->second += it.second;
        } else {
            state.insert({it.first, it.second});
        }
    }
}

bool validateState(std::map<int, int> state, std::map<int, int> transaction)
{
    bool returner = true;
    int total = 0;
    for (auto& it : transaction) {
        total += it.second;
        auto keyValPair = state.find(it.first);
        if (keyValPair != state.end() && keyValPair->second < it.second * -1) {
            returner = false;
        }
    }
    if (total != 0) {
        returner = false;
    }
    return returner;
}

Block makeBlock(std::list<std::map<int, int>> transactions, std::list<Block> chain)
{
    Block parent_block = *chain.rbegin();
    std::string parent_hash = parent_block.getHash();
    int block_number = parent_block.getContents().getBlockNumber() + 1;
    int transaction_count = transactions.size();
    BlockContents contents(block_number, parent_hash, transaction_count, transactions);
    std::string block_hash = contents.hash_contents();

    Block output(block_hash, contents);
    return output;
}

std::list<Block> BlockChain::getChain()
{
    return chain;
}

void checkBlockHash(Block block) {
    std::string expected_hash = block.getContents().hash_contents();

    if (block.getHash() != expected_hash) {
        throw 1;
    }
}

std::map<int, int> checkBlockValidity(Block block, Block parent, std::map<int, int> state) {
    int parent_block_number = parent.getContents().getBlockNumber();
    std::string parent_hash = parent.getHash();
    int block_number = block.getContents().getBlockNumber();

    for (auto transaction : block.getContents().getTransactions()) {
        if (validateState(state, transaction)) {
            updateState(state, transaction)
        } else {
            throw 1;
        }
    }

    checkBlockHash(block);

    if (block_number != (parent_block_number + 1)) {
        throw 1;
    }

    if (block.getContents().getParentHash() != parent_hash) {
        throw 1;
    }

    return state;
}