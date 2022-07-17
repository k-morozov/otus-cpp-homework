cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

set(APP_NAME test_ip_filter)

add_executable(${APP_NAME})

target_sources(${APP_NAME} PUBLIC
        main.cpp
        utest.cpp
# code
        ../src/Pool.cpp
)

include_directories(${CONAN_INCLUDE_DIRS})
target_link_libraries(${APP_NAME}
        ${CONAN_LIBS}
        )

add_test(NAME ${APP_NAME} COMMAND $<TARGET_FILE:${APP_NAME}>)