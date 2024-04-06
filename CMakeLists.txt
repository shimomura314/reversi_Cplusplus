cmake_minimum_required(VERSION 3.29)
project(Othello CXX)

# # C++のバージョン指定
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Python EXACT 3.9 COMPONENTS Interpreter Development)
list(APPEND CMAKE_PREFIX_PATH "C:/Users/shimomura/anaconda3/Lib/site-packages/pybind11/share/cmake/pybind11")
find_package(pybind11 REQUIRED)

# ターゲット（Pythonモジュール）の追加
pybind11_add_module(othello
    bitboard/c2python.cpp
    bitboard/othello.cpp
    bitboard/bitboard.cpp
    strategy/basestrategy.cpp
    strategy/strategy.cpp
    strategy/random.cpp
    strategy/maximize.cpp
    strategy/minimize.cpp
    strategy/minmax.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")