cmake_minimum_required(VERSION 3.24)
project(algos)

set(CMAKE_CXX_STANDARD 17)

add_executable(algos main.cpp sorting.h sorting.cpp utilities.h binary_search.h binary_search.cpp dfs.h dfs.cpp backtracking.h backtracking.cpp)
