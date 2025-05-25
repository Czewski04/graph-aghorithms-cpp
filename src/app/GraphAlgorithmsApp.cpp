//
// Created by wiktor on 11.05.2025.
//

#include "GraphAlgorithmsApp.h"
#include "FileReader.h"
#include "MSTSolver.h"
#include "ShortestPathSolver.h"
#include "MaximumFlowSolver.h"
#include "GraphGenerator.h"
#include "FileCreator.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>


[[noreturn]] void GraphAlgorithmsApp::runApp() {
    showMenu();
    switch (getUserChoice()) {
        case 1:
            while (true) {
                showMSTMenu();
                switch (getUserChoice()) {
                    case 1:
                        FileReader::readFile(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex);
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 2:
                        GraphGenerator::generateGraphForMST(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, 1, 1);
                        //showAdjacencyMatrix();
                        //showNeighboursList();
                        break;
                    case 3:
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 4:
                        std::tie(MSTEdgesList, MSTEdgesCount, MSTWeight, operationTime) = MSTSolver::primsAlgorithmForMatrix(adjacencyMatrix, verticesNumber);
                        std::cout<<"Matrix: \n";
                        showMSTResults();
                        std::tie(MSTEdgesList, MSTEdgesCount, MSTWeight, operationTime) = MSTSolver::primsAlgorithmForList(neighboursList, verticesNumber);
                        std::cout<<"List: \n";
                        showMSTResults();
                        break;
                    case 5:
                        std::tie(MSTEdgesList, MSTEdgesCount, MSTWeight, operationTime) = MSTSolver::kruskalsAlgorithmForMatrix(adjacencyMatrix, verticesNumber);
                        std::cout<<"Matrix: \n";
                        showMSTResults();
                        std::tie(MSTEdgesList, MSTEdgesCount, MSTWeight, operationTime) = MSTSolver::kruskalsAlgorithmForList(neighboursList, verticesNumber);
                        std::cout<<"List: \n";
                        showMSTResults();
                        break;
                    default: ;
                }
            }
        case 2:
            while (true) {
                showShortestPathMenu();
                switch (getUserChoice()) {
                    case 1:
                        FileReader::readFile(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex);
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 2:
                        GraphGenerator::generateGraphForShortestPathAndMaxFlow(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex, 1, 1);
                        //showAdjacencyMatrix();
                        //showNeighboursList();
                        break;
                    case 3:
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 4:
                        std::tie(shortestPathsList, shortestPathsDistances, operationTime) = ShortestPathSolver::dijkstrasAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex);
                        std::cout<<"Matrix: \n";
                        showShortestPathsResult();
                        std::tie(shortestPathsList, shortestPathsDistances, operationTime) = ShortestPathSolver::dijkstrasAlgorithmForList(neighboursList, verticesNumber, startVertex);
                        std::cout<<"List: \n";
                        showShortestPathsResult();
                        break;
                    case 5:
                        std::tie(shortestPathsList, shortestPathsDistances, operationTime) = ShortestPathSolver::bellmanFordAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex);
                        std::cout<<"Matrix: \n";
                        showShortestPathsResult();
                        std::tie(shortestPathsList, shortestPathsDistances, operationTime) = ShortestPathSolver::bellmanFordAlgorithmForList(neighboursList, verticesNumber, startVertex);
                        std::cout<<"List: \n";
                        showShortestPathsResult();
                        break;
                    default: ;
                }
            }
        case 3:
            while (true) {
                showMaxFlowMenu();
                switch (getUserChoice()) {
                    case 1:
                        FileReader::readFile(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex);
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 2:
                        GraphGenerator::generateGraphForShortestPathAndMaxFlow(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex,1, 1);
                        //showAdjacencyMatrix();
                        //showNeighboursList();
                        break;
                    case 3:
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 4:
                        std::tie(maxFlow, operationTime) = MaximumFlowSolver::fordFulkersonDfsAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex, endVertex);
                        std::cout<<"Matrix: \n";
                        showMaxFlowResult();
                        std::tie(maxFlow, operationTime) = MaximumFlowSolver::fordFulkersonDfsAlgorithmForList(neighboursList, verticesNumber, startVertex, endVertex);
                        std::cout<<"List: \n";
                        showMaxFlowResult();
                        break;
                    case 5:
                        std::tie(maxFlow, operationTime) = MaximumFlowSolver::fordFulkersonBfsAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex, endVertex);
                        std::cout<<"Matrix: \n";
                        showMaxFlowResult();
                        std::tie(maxFlow, operationTime) = MaximumFlowSolver::fordFulkersonBfsAlgorithmForList(neighboursList, verticesNumber, startVertex, endVertex);
                        std::cout<<"List: \n";
                        showMaxFlowResult();
                        break;
                    case 6:
                        FileCreator::generateFile(adjacencyMatrix, verticesNumber, edgesNumber);
                    default: ;
                }
            }
        case 4:
            runAllAlgorithmTests();
            break;
        default: ;
    }
    std::exit(0);
}

int GraphAlgorithmsApp::getUserChoice() {
    int userChoice=0;
    std::cin >> userChoice;
    return userChoice;
}

void GraphAlgorithmsApp::showNeighboursList() {
    for (int i=0; i<verticesNumber; i++) {
        std::cout<<i<<". ";
        neighbour* current = neighboursList[i];
        while (current!=nullptr) {
            std::cout<<"("<<current -> vertex<<", "<<current -> weight<<") ";
            current = current -> nextVertex;
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

void GraphAlgorithmsApp::showAdjacencyMatrix() {
    std::cout << "   ";
    for (int i = 0; i < verticesNumber; ++i) {
        std::cout << std::setw(4) << i << " ";
    }
    std::cout << "\n";

    std::cout << "----";
    for (int i = 0; i < verticesNumber; ++i) {
        std::cout << "-----";
    }
    std::cout << "\n";

    for (int i = 0; i < verticesNumber; ++i) {
        std::cout << std::setw(2) << i << "|";
        for (int j = 0; j < verticesNumber; ++j) {
            std::cout << std::setw(4) << adjacencyMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void GraphAlgorithmsApp::showMenu() {
    std::cout<<"1. Minimum Spanning Tree Problem.\n"<<
        "2. Shortest Path Problem.\n"
        "3. Maximum Flow Problem.\n"
        "4. Run all algorithms.\n";
}

void GraphAlgorithmsApp::showMSTMenu() {
    std::cout<<"1. Read graph from file.\n"<<
        "2. Generate graph.\n"
        "3. Show graph.\n"
        "4. Prim's algorithm\n"
        "5. Kruskal's algorithm\n";
}

void GraphAlgorithmsApp::showShortestPathMenu() {
    std::cout<<"1. Read graph from file.\n"<<
        "2. Generate graph.\n"
        "3. Show graph.\n"
        "4. Dijkstra's algorithm\n"
        "5. Bellman-Ford algorithm\n";
}

void GraphAlgorithmsApp::showMaxFlowMenu() {
    std::cout<<"1. Read graph from file.\n"<<
        "2. Generate graph.\n"
        "3. Show graph.\n"
        "4. DFS Ford-Fulkerson algorithm\n"
        "5. BFS Ford-Fulkerson algorithm\n"
        "6. Export graph file\n";
}

void GraphAlgorithmsApp::showMSTResults() {
    for (int i = 0; i < MSTEdgesCount; ++i) {
        std::cout<<MSTEdgesList[i].u<<" -- "<<MSTEdgesList[i].v<<"  |weight: "<<MSTEdgesList[i].weight<<"\n";
    }
    std::cout<<"Summary MST weight: "<<MSTWeight<<"\n";
    std::cout<<"Operation Time: "<<operationTime<<"\n";
    std::cout<<"\n\n";
}

void GraphAlgorithmsApp::showShortestPathsResult() {
    for (int i=0; i<verticesNumber; i++) {
        neighbour* current = shortestPathsList[i];
        while (current!=nullptr) {
            std::cout<<current -> vertex<<" -> ";
            current = current -> nextVertex;
        }
        std::cout<<"  total distance: "<<shortestPathsDistances[i];
        std::cout<<"\n";
    }
    std::cout<<"Operation Time: "<<operationTime<<"\n";
    std::cout<<"\n\n";
}

void GraphAlgorithmsApp::showMaxFlowResult() const {
    std::cout<<"Maximum graph flow from "<<startVertex<<"to "<<endVertex<<": "<<maxFlow<<"\n";
    std::cout<<"Operation Time: "<<operationTime<<"\n";
    std::cout<<"\n\n";
}

struct BenchmarkResult {
    std::map<std::string, double> results;

    void add(const std::string& name, int size, int density, double time) {
        std::ostringstream key;
        key << name << "_" << size << "_" << density;
        results[key.str()] = time;
    }

    void save(const std::string& filename) const {
        std::ofstream out(filename);
        for (const auto& [key, val] : results) {
            out << key << " = " << val << "\n";
        }
        out.close();
    }
};

void GraphAlgorithmsApp::runAllAlgorithmTests() {
    const int runs = 25;
    const std::vector<int> sizes = {80, 100, 120, 140, 170, 200, 250};
    const std::vector<int> densities = {20, 60, 99};
    BenchmarkResult bench;

    for (int size : sizes) {
        for (int density : densities) {
            double total_prim_list = 0, total_prim_matrix = 0;
            double total_kruskal_list = 0, total_kruskal_matrix = 0;
            double total_dijkstra_list = 0, total_dijkstra_matrix = 0;
            double total_bellman_list = 0, total_bellman_matrix = 0;
            double total_ffdfs_list = 0, total_ffdfs_matrix = 0;
            double total_ffbfs_list = 0, total_ffbfs_matrix = 0;

            for (int i = 0; i < runs; ++i) {
                std::cout<<"size: "<<size<<" , density: "<<density<<" run: "<<i<<"\n";
                GraphGenerator::generateGraphForMST(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, size, density);

                auto [p_list, _, __, t_prim_list] = MSTSolver::primsAlgorithmForList(neighboursList, verticesNumber);
                auto [p_matrix, ___, ____, t_prim_matrix] = MSTSolver::primsAlgorithmForMatrix(adjacencyMatrix, verticesNumber);
                auto [k_list, _____, ______, t_kruskal_list] = MSTSolver::kruskalsAlgorithmForList(neighboursList, verticesNumber);
                auto [k_matrix, _______, ________, t_kruskal_matrix] = MSTSolver::kruskalsAlgorithmForMatrix(adjacencyMatrix, verticesNumber);

                total_prim_list += t_prim_list;
                total_prim_matrix += t_prim_matrix;
                total_kruskal_list += t_kruskal_list;
                total_kruskal_matrix += t_kruskal_matrix;

                GraphGenerator::generateGraphForShortestPathAndMaxFlow(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex, size, density);

                auto [___7, ___8, t_dijkstra_list] = ShortestPathSolver::dijkstrasAlgorithmForList(neighboursList, verticesNumber, startVertex);
                auto [___1, ___2, t_dijkstra_matrix] = ShortestPathSolver::dijkstrasAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex);
                auto [___3, ___4, t_bellman_list] = ShortestPathSolver::bellmanFordAlgorithmForList(neighboursList, verticesNumber, startVertex);
                auto [___5, ___6, t_bellman_matrix] = ShortestPathSolver::bellmanFordAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex);
                auto [fdfs_matrix, t_ffdfs_matrix] = MaximumFlowSolver::fordFulkersonDfsAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex, endVertex);
                auto [fdfs_list, t_ffdfs_list] = MaximumFlowSolver::fordFulkersonDfsAlgorithmForList(neighboursList, verticesNumber, startVertex, endVertex);
                auto [ffbfs_matrix, t_ffbfs_matrix] = MaximumFlowSolver::fordFulkersonBfsAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex, endVertex);
                auto [ffbfs_list, t_ffbfs_list] = MaximumFlowSolver::fordFulkersonBfsAlgorithmForList(neighboursList, verticesNumber, startVertex, endVertex);

                total_dijkstra_list += t_dijkstra_list;
                total_dijkstra_matrix += t_dijkstra_matrix;
                total_bellman_list += t_bellman_list;
                total_bellman_matrix += t_bellman_matrix;
                total_ffdfs_list += t_ffdfs_list;
                total_ffdfs_matrix += t_ffdfs_matrix;
                total_ffbfs_list += t_ffbfs_list;
                total_ffbfs_matrix += t_ffbfs_matrix;

            }

            bench.add("prim_list", size, density, total_prim_list / runs);
            bench.add("prim_matrix", size, density, total_prim_matrix / runs);
            bench.add("kruskal_list", size, density, total_kruskal_list / runs);
            bench.add("kruskal_matrix", size, density, total_kruskal_matrix / runs);
            bench.add("dijkstra_list", size, density, total_dijkstra_list / runs);
            bench.add("dijkstra_matrix", size, density, total_dijkstra_matrix / runs);
            bench.add("bellman_list", size, density, total_bellman_list / runs);
            bench.add("bellman_matrix", size, density, total_bellman_matrix / runs);
            bench.add("ffdfs_list", size, density, total_ffdfs_list / runs);
            bench.add("ffdfs_matrix", size, density, total_ffdfs_matrix / runs);
            bench.add("ffbfs_list", size, density, total_ffbfs_list / runs);
            bench.add("ffbfs_matrix", size, density, total_ffbfs_matrix / runs);
        }
    }

    bench.save("benchmark_results.txt");
}
