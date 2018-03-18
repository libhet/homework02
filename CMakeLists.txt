cmake_minimum_required(VERSION 3.2)

IF($ENV{TRAVIS_BUILD_NUMBER})
    project(homework02 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
ELSE()
    project(homework02 VERSION 0.0.1)
ENDIF()

set(CMAKE_CXX_STANDARD 14)

add_executable(ip_filter ip_filter.cpp)

set_target_properties(ip_filter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT shadow.balz@mail.ru)

include(CPack)
