cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)

project(3d-importer VERSION 1.0.0)

if (DEFINED ENV{GEODE_SDK})
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
    include("$ENV{GEODE_SDK}/share/geode/cmake/GeodeFile.cmake")
else()
    find_package(Geode REQUIRED)
endif()

setup_geode_mod(
    3d-importer
    SOURCES
        src/main.cpp
)
