cmake_minimum_required(VERSION 3.19)
project(Algorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fsanitize=address -g")
set(Boost_INCLUDE_DIR /opt/homebrew/Cellar/boost/1.76.0/include)
set(Boost_LIBRARY_DIR /opt/homebrew/Cellar/boost/1.76.0/lib)
find_package(Boost 1.76.0 COMPONENTS system filesystem REQUIRED)
add_executable(Algorithms main.cpp Bag.hpp Queue.h Stack.hpp SelectionSort.hpp WeightedQuickUnionUF.hpp WeightedQuickUnionUF.cpp InsertionSort.hpp Comparable.hpp ShellSort.hpp MergeSort.h)
include_directories(${Boost_INCLUDE_DIR})
