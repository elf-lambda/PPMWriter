cmake_minimum_required(VERSION 3.29)
project(learn01)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Using Clang Compiler :)")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra -Wpedantic -O2")
endif()

add_executable(learn01 main.cc
        MFont.hh
        PPMWriter.hh
        MUtils.hh
)