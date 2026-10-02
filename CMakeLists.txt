cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)

project(3d-importer)

find_package(Geode REQUIRED)

add_geode_mod(
    3d-importer
    "puttipongnark2558-creator.3d_importer"
    src/main.cpp
    src/Import3DPopup.cpp
)
