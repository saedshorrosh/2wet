cmake_minimum_required(VERSION 3.22)
project(2wet)

set(CMAKE_CXX_STANDARD 11)

add_executable(2wet main.cpp DynamicArray.h HashTable.h AvlTree.h Employee.h disjoint_set.h Node.h UpTreeNode.h Company.h)
