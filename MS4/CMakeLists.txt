cmake_minimum_required(VERSION 3.27)
project(MS4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(MS4
        "Date copy.cpp"
        "Date copy.h"
        Lib.h
        LibApp.cpp
        LibApp.h
        Menu.cpp
        Menu.h
        ms4_tester.cpp
        Publication.cpp
        Publication.h
        Streamable.cpp
        Streamable.h
        Utils.cpp
        Utils.h
        Book.cpp
        Book.h)
