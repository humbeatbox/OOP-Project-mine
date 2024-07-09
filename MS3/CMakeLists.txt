cmake_minimum_required(VERSION 3.27)
project(MS3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(MS3
        Date.cpp
        Date.h
        LibApp.cpp
        LibApp.h
        Menu.cpp
        Menu.h
        ms3_tester.cpp
        Utils.cpp
        Utils.h
        Lib.h
        Publication.cpp
        Publication.h
        Streamable.cpp
        Streamable.h)
