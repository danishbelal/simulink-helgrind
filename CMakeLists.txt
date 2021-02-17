cmake_minimum_required(VERSION 3.11)

project(SimulinkMultithreadingValgrind
        LANGUAGES C CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(Threads REQUIRED)

add_subdirectory(Model)
add_subdirectory(Source)