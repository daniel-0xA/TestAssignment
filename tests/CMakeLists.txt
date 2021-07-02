cmake_minimum_required(VERSION 3.19)
project(TestAssignment)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tests Tests.cpp catch2/catch.hpp)