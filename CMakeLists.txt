cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)

project(3d-importer VERSION 1.0.0)

find_package(Geode REQUIRED)

setup_geode_mod(
    3d-importer
    SOURCES
        src/main.cpp
)
