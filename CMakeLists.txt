cmake_minimum_required(VERSION 3.12)
project(BTree)

set(CMAKE_CXX_STANDARD 14)

add_executable(BTree main.cpp BTree.h Status.h Record.h BTree.cpp DeleteBTree.h DeleteBTree.cpp)