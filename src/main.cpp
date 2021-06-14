#include <iostream>
#include <map>
#include <string>
#include <random>
#include "../lib/sha256.h"


std::mt19937_64 rng;
std::uniform_int_distribution<int> uni(0, 3);

std::map<int, int> generateTransactions(int MaxVal);

void updateState(std::map<int,int> state, std::map<int,int> transaction);
bool validateState(std::map<int,int> state, std::map<int,int> transaction);

int main() {
    // Random ledger generation test


    for (int i = 2; i < 100000; i++) {
        std::map<int, int> temp = generateTransactions(i);
    }

    // String hashing test

    std::string src_str = "Hello World!";
    std::string hash_str;

    sha256::hash256_hex_string(src_str, hash_str);

    std::cout << hash_str << std::endl;

    return 0;
}
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


std::map<int, int> generateTransactions(int MaxVal) {
    std::uniform_int_distribution<int> distro(0, MaxVal);
    int random_bit = uni(rng);
    int random_integer = distro(rng);
    int sign = (random_bit * 2) - 1;
    int amount = random_integer * sign;
    std::map<int, int> vals = {{1, amount},
                               {2, amount * -1}};
    return vals;
}

