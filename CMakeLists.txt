cmake_minimum_required(VERSION 3.20)

include(FetchContent)

project(3d-importer VERSION 1.0.0 LANGUAGES CXX)

find_package(Geode REQUIRED)

setup_geode_mod(3d-importer)

add_subdirectory(src)
