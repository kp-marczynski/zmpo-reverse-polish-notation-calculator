cmake_minimum_required(VERSION 3.8)
project(ZMPO_lista3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Tree.cpp Tree.h Interface.cpp Interface.h Node.cpp Node.h NodeType.h ErrorLogger.cpp ErrorLogger.h)
add_executable(ZMPO_lista3 ${SOURCE_FILES})