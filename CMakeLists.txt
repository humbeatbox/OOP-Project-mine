cmake_minimum_required(VERSION 3.27)
project(OOP_Project_mine)

set(CMAKE_CXX_STANDARD 14)

include_directories(MS1)
include_directories(MS2)
include_directories(MS5)

add_executable(OOP_Project_mine
        MS1/Date.cpp
        MS1/Date.h
        MS1/dateTester.cpp
        MS1/Menu.cpp
        MS1/Menu.h
        MS1/menuTester.cpp
        MS1/ms1_tester.cpp
        MS1/Utils.cpp
        MS1/Utils.h
        MS2/LibApp.cpp
        MS2/LibApp.h
        MS2/Menu.cpp
        MS2/Menu.h
        MS2/ms2_tester.cpp
        MS2/Utils.cpp
        MS2/Utils.h
        MS3/ms3_tester.cpp
        MS4/ms4_tester.cpp
        MS5/LibAppMain.cpp
        MS5/PublicationSelector.cpp
        MS5/PublicationSelector.h
        MS5/pubSel_Tester.cpp)
