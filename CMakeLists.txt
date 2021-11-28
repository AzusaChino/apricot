cmake_minimum_required(VERSION 3.20.0)

include("cmake/hunter-gate.cmake")
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.18.16.tar.gz"
        SHA1 "6cbca2b0e7605ad8ea22ee3527850996436f71b8"
)

project(apricot VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

### download dependencies ###
hunter_add_package(GTest)

find_package(GTest CONFIG REQUIRED)

### Targets
add_executable(apricot main.cc)
### Test Targets
add_executable(hunter_simple module.cc module_test.cc)
target_link_libraries(hunter_simple PUBLIC GTest::main)

### Testing ###
enable_testing()

add_test(NAME SimpleTest COMMAND hunter_simple)
