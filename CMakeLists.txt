cmake_minimum_required(VERSION 3.30)
project(graphAlgorithms)

set(CMAKE_CXX_STANDARD 20)
include_directories(
        include/app
        include/io
        include/structure
)
add_executable(graphAlgorithms
        src/app/Main.cpp
        src/app/GraphAlgorithmsApp.cpp
        src/io/FileReader.cpp
)
