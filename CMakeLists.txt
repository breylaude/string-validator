cmake_minimum_required(VERSION 3.19)
project(StringValidator)

set(CMAKE_CXX_STANDARD 17)

add_executable(StringValidator
        include/StringValidator.h
        src/StringValidator.cpp
        test/test.cpp)
