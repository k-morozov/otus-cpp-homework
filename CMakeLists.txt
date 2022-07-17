cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
set(CONAN_DISABLE_CHECK_COMPILER True)
conan_basic_setup()

enable_testing()

add_subdirectory(ip_filter)

