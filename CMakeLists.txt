cmake_minimum_required(VERSION 3.20.0)

project(apricot VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(apricot main.cpp)
