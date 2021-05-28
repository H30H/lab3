cmake_minimum_required(VERSION 3.19)
project(lab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab3 main.cpp Sources/myBinaryTree.cpp Sources/myLinkedList.cpp Sources/myStack.cpp Headers/myStack.h Sources/mySet.cpp Headers/mySet.h Sources/myQueue.cpp Headers/myQueue.h tests/test.cpp tests/test.h)