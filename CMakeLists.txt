cmake_minimum_required(VERSION 3.15)
project(fileIO)

set(CMAKE_CXX_STANDARD 14)

add_executable(fileIO fileIO.cpp Record.h Record.cpp)