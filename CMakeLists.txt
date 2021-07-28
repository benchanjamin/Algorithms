cmake_minimum_required(VERSION 3.19)
project(Algorithms)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fsanitize=address -g")
add_executable(Algorithms main.cpp Bag.h Queue.h Stack.h WeightedUF.h)
