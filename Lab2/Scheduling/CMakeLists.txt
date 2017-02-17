cmake_minimum_required(VERSION 3.6)
project(Scheduling)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp scheduling.h)
add_executable(Scheduling ${SOURCE_FILES})