cmake_minimum_required(VERSION 3.22)
project(filter_ip)

set(CMAKE_CXX_STANDARD 17)

add_executable(filter_ip
        src/main.cpp
        src/utils.h
        src/utils.cpp
)

enable_testing()

add_subdirectory(test)
