cmake_minimum_required(VERSION 3.22)
project(syntax_analyzer)

set(CMAKE_CXX_STANDARD 14)

add_executable(syntax_analyzer main.cpp ControlTable.cpp ControlTable.h)
