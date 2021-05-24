cmake_minimum_required(VERSION 3.19)
project(lab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab3 main.cpp headers/myBinaryTree.cpp headers/myLinkedList.cpp headers/myStack.cpp sources/myStack.h headers/mySet.cpp sources/mySet.h headers/myQueue.cpp sources/myQueue.h)