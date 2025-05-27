cmake_minimum_required(VERSION 3.30)
project(graphAlgorithms)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,536870912") #powiększenie stosu do 512MB
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -static-libgcc -static-libstdc++ -static")

include_directories(
        include/app
        include/io
        include/data_structures
        include/algorithms
        include/utilities
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
        src/io/GraphGenerator.cpp
        src/utilities/Utilities.cpp
)
