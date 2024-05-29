cmake_minimum_required(VERSION 3.27)
project(algo3)

set(CMAKE_CXX_STANDARD 17)

add_executable(algo3 main.cpp
        board.cpp
        board.hpp
        piece.cpp
        piece.hpp
        ai.cpp
        ai.hpp
        game.cpp
        game.hpp)
