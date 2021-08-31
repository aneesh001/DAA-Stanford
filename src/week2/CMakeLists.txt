cmake_minimum_required(VERSION 3.10)

project(Week2 VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(Week2Config.h.in Week2Config.h)

add_executable(Week2 quicksort.cpp)

target_include_directories(Week2 PUBLIC "${PROJECT_BINARY_DIR}")

