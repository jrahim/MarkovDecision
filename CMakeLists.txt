# cmake_minimum_required(VERSION <specify CMake version here>)
project(MarkovDecision)

set(CMAKE_CXX_STANDARD 14)

add_executable(MarkovDecision
        README.md SamplingTreeNode.cpp SamplingTreeNode.h Samplingtree.cpp Samplingtree.h main.cpp)
