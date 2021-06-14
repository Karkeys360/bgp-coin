cmake_minimum_required(VERSION 3.19)
project(bgp_coin)

set(CMAKE_CXX_STANDARD 20)

add_executable(bgp_coin src/main.cpp lib/sha256.h)
