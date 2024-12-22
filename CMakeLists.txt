# cmake ..
# cmake --build .

cmake_minimum_required(VERSION 3.29)
project(Othello CXX)

# # C++のバージョン指定
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Python COMPONENTS Interpreter Development)
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

if(MSVC)
    # Visual C++ コンパイラ用のオプション
    add_compile_options(/W4)
else()
    # GCCやClangなどのコンパイラ用のオプション
    add_compile_options(-Wall -Wextra -Werror)
endif()
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set_target_properties(othello PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bitboard"
)