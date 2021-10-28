cmake_minimum_required(VERSION 3.17)
project(WhiteRobotOriginal)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(WhiteRobotOriginal
        index_data.CSV
        RobotMenu.cpp
        RobotMenu.h
        WhiteRobot.cpp
        WhiteRobot.h
        WhiteRobotC.cpp)
