cmake_minimum_required(VERSION 3.29)
project(MinesweeperCLI)

set(CMAKE_CXX_STANDARD 20)

add_executable(MinesweeperCLI main.cpp
        Grid.cpp
        Grid.h
        Square.cpp
        Square.h
        Game.cpp
        Game.h
        TermColor.h
        TermColor.cpp)
