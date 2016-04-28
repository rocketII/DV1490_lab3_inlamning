cmake_minimum_required(VERSION 3.3)
project(inlamning3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES EngWord.h HashTable.h Hash.h main.cpp) #
add_executable(inlamning3 ${SOURCE_FILES})

