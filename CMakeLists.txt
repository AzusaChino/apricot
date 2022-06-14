cmake_minimum_required(VERSION 3.16.0)

project(apricot VERSION 1.0.0 LANGUAGES C CXX)

include_directories(include)

### Testing ###
enable_testing()

add_executable(apricot main.cc)
