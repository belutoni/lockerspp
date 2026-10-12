cmake_minimum_required(VERSION 4.3)
project(lockerspp)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(lockerspp
        lockerspp.h
        main.cpp)
