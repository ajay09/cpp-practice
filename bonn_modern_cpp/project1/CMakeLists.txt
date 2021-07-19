cmake_minimum_required(VERSION 3.10)
project(first_project)

# Set build type if not set
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 17) #  --std=c++17
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0") # -g adds debug info in binary
                                    # -O<num> : 0, 1, 2, 3  optimization levels

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # generates the json file that contains the compile commands executed by make

add_library(tools ../tools.cpp)
add_executable(main ../main.cpp)
target_link_libraries(main tools)
