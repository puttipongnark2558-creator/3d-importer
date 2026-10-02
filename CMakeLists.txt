cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)

project(3d-importer VERSION 1.0.0)

include(FetchContent)
FetchContent_Declare(
    Geode
    GIT_REPOSITORY https://github.com/geode-sdk/geode.git
    GIT_TAG v3.1.0
)
FetchContent_MakeAvailable(Geode)

setup_geode_mod(
    3d-importer
    SOURCES
        src/main.cpp
)
