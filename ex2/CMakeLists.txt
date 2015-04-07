cmake_minimum_required(VERSION 2.8.4)
project(ex2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")

set(SOURCE_FILES Piece.cpp Pawn.cpp Knight.cpp Bishop.cpp Rook.cpp Queen.cpp King.cpp Board.cpp
 chess.cpp)
add_executable(ex2 ${SOURCE_FILES})