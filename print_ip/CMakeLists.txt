cmake_minimum_required(VERSION 3.22)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

set(APP_NAME print_ip)
project(${APP_NAME} VERSION ${PROJECT_VERSION})

configure_file(src/version.h.in src/version.h)

include_directories(include)

set(CMAKE_CXX_STANDARD 20)

add_executable(${APP_NAME}
        src/main.cpp
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