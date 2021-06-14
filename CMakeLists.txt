cmake_minimum_required(VERSION 3.19)
project(TestAssignment)

set(CMAKE_CXX_STANDARD 17)

add_executable(TestAssignment src/main.cpp src/ArgumentsParser.cpp src/ReadImageData.cpp src/FileHeader.h)