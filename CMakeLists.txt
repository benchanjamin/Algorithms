cmake_minimum_required(VERSION 3.19)
project(Algorithms)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fsanitize=address -g
-DBOOST_ROOT=/opt/homebrew/Cellar/boost/1.76.0")
set(Boost_INCLUDE_DIR /opt/homebrew/Cellar/boost/1.76.0/include)
set(Boost_LIBRARY_DIR /opt/homebrew/Cellar/boost/1.76.0/lib)
find_package(Boost 1.76.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_executable(Algorithms main.cpp Bag.h Queue.h Stack.h SelectionSort.h WeightedUF.h WeightedUF.cpp InsertionSort.h Comparable.h ShellSort.h)
