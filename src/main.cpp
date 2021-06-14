#include <iostream>
#include <map>
#include <string>
#include <random>
#include "../lib/sha256.h"


std::mt19937_64 rng;
std::uniform_int_distribution<int> uni(0, 3);

std::map<std::string, int> generateTransactions(int MaxVal);

int main()
{
    // Random ledger generation test

    for (int i = 2; i < 100000; i++) {
        std::map<std::string, int> temp = generateTransactions(i);
        std::cout << "Person1 = " << temp.find("Person1")->second << " Person2 = "
                  << temp.find("Person2")->second << std::endl;

    }

    // String hashing test

    std::string src_str = "Hello World!";
    std::string hash_str;

    sha256::hash256_hex_string(src_str, hash_str);

    std::cout << hash_str << std::endl;

    return 0;
}

std::map<std::string, int> generateTransactions(int MaxVal)
{
    std::uniform_int_distribution<int> distro(0, MaxVal);
    int random_bit = uni(rng);
    int random_integer = distro(rng);
    int sign = (random_bit * 2) - 1;
    int amount = random_integer * sign;
    std::map<std::string, int> vals = {{"Person1", amount},
                                       {"Person2", amount * -1}};
    return vals;
}
