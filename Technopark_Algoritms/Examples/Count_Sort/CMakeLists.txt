cmake_minimum_required(VERSION 3.6)
project(Count_sort)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Count_sort ${SOURCE_FILES})