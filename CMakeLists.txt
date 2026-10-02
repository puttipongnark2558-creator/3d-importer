cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)

project(3d-importer VERSION 1.0.0)

include("${GEODE_SDK}/share/geode/cmake/GeodeFile.cmake")

setup_geode_mod(
    3d-importer
    SOURCES
        src/main.cpp
)
