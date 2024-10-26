cmake_minimum_required(VERSION 3.16)
project(DistributedSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics)

set(SOURCES src/main.cpp src/node.cpp)

add_executable(DistributedSim ${SOURCES})
target_link_libraries(DistributedSim PRIVATE sfml-graphics)
target_include_directories(DistributedSim PRIVATE include)