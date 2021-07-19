cmake_minimum_required(VERSION 3.10)
project(GoogleCpp)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDART 11) # --std=c++11
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")  # -g adds debug info in binary
                                     # -O0 sets optimisation to no-optimisation

                                     
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # generates a json file that contains the compile commands executed by make.

add_executable(random random.cpp)

