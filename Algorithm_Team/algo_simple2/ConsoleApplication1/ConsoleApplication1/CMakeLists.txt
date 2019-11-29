cmake_minimum_required(VERSION 3.15)
project(ConsoleApplication1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ConsoleApplication1
        ConsoleApplication1.cpp
        Coordinate.cpp
        Coordinate.h
        Problem.cpp
        Problem.h
        State.cpp
        State.h)
