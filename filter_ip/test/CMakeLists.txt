cmake_minimum_required(VERSION 3.21)

set(APP_NAME test-print_ip)

add_executable(${APP_NAME})

target_sources(${APP_NAME} PUBLIC
        main.cpp
        utest.cpp
# code
        ../src/utils.cpp
)

target_link_libraries(${APP_NAME}
        ${CONAN_LIBS}
        )

add_test(NAME ${APP_NAME} COMMAND $<TARGET_FILE:${APP_NAME}>)