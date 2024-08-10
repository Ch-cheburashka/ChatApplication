cmake_minimum_required(VERSION 3.0.0)

project(include/smart_pointers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cli cli/cli.cpp)