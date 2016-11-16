cmake_minimum_required(VERSION 3.6)
project(C_Laba1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror")

set(SOURCE_FILES main.c)
add_executable(C_Laba1 ${SOURCE_FILES})