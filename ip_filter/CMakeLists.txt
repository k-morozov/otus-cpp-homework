cmake_minimum_required(VERSION 3.22)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

set(APP_NAME ip_filter)
project(${APP_NAME} VERSION ${PROJECT_VERSION})

configure_file(src/version.h.in src/version.h)

set(CMAKE_CXX_STANDARD 20)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/static/ip_filter.tsv
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/static)

add_executable(${APP_NAME}
        src/main.cpp
        src/Pool.cpp
)

add_subdirectory(test)

install(TARGETS ${APP_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT k_morozov@vk.com)

set(CPACK_PACKAGE_NAME ${APP_NAME})

include(CPack)