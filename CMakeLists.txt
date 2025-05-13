cmake_minimum_required(VERSION 3.30)
project(graphAlgorithms)

set(CMAKE_CXX_STANDARD 20)
include_directories(
        include/app
        include/io
        include/data_structures
        include/algorithms
)
add_executable(graphAlgorithms
        src/app/Main.cpp
        src/app/GraphAlgorithmsApp.cpp
        src/io/FileReader.cpp
        src/algorithms/MaximumFlowSolver.cpp
        src/algorithms/MSTSolver.cpp
        src/algorithms/ShortestPathSolver.cpp
        src/data_structures/MinimumHeap.cpp
        src/data_structures/UnionFind.cpp
)
