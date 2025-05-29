//
// Created by wiktor on 11.05.2025.
//

#include "GraphAlgorithmsApp.h"
#include "FileReader.h"
#include "MSTSolver.h"
#include "ShortestPathSolver.h"
#include "MaximumFlowSolver.h"
#include "GraphGenerator.h"
#include <iostream>
#include <iomanip>


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
                        GraphGenerator::generateGraphForMST(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber);
                        showAdjacencyMatrix();
                        showNeighboursList();
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
                        GraphGenerator::generateGraphForShortestPathAndMaxFlow(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex);
                        showAdjacencyMatrix();
                        showNeighboursList();
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
                int** residualGraphMatrix;
                neighbour** residualGraphList;
                showMaxFlowMenu();
                switch (getUserChoice()) {
                    case 1:
                        FileReader::readFile(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex);
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 2:
                        GraphGenerator::generateGraphForShortestPathAndMaxFlow(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex);
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 3:
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 4:
                        std::cout<<"Matrix: \n";
                        std::tie(maxFlow, operationTime, residualGraphMatrix) = MaximumFlowSolver::fordFulkersonDfsAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex, endVertex);
                        showFlowMatrix(residualGraphMatrix);
                        showMaxFlowResult();
                        std::cout<<"List: \n";
                        std::tie(maxFlow, operationTime, residualGraphList) = MaximumFlowSolver::fordFulkersonDfsAlgorithmForList(neighboursList, verticesNumber, startVertex, endVertex);
                        showFlowList(residualGraphList);
                        showMaxFlowResult();
                        break;
                    case 5:
                        std::cout<<"Matrix: \n";
                        std::tie(maxFlow, operationTime, residualGraphMatrix) = MaximumFlowSolver::fordFulkersonBfsAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex, endVertex);
                        showFlowMatrix(residualGraphMatrix);
                        showMaxFlowResult();
                        std::cout<<"List: \n";
                        std::tie(maxFlow, operationTime, residualGraphList) = MaximumFlowSolver::fordFulkersonBfsAlgorithmForList(neighboursList, verticesNumber, startVertex, endVertex);
                        showFlowList(residualGraphList);
                        showMaxFlowResult();
                        break;
                    default: ;
                }
            }
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
        "3. Maximum Flow Problem.\n";
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
        "5. BFS Ford-Fulkerson algorithm\n";
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

void GraphAlgorithmsApp::showFlowMatrix(int** residualGraph) {
    int totalCapacity = 0;
    int totalFlow = 0;
    for (int i = 0; i < verticesNumber; i++) {
        for (int j = 0; j < verticesNumber; j++) {
            totalCapacity += adjacencyMatrix[i][j];
        }
    }

    std::cout << "Flow on edges:\n";
    for (int i = 0; i < verticesNumber; i++) {
        for (int j = 0; j < verticesNumber; j++) {
            if (adjacencyMatrix[i][j] > 0) {
                int net_flow_on_edge = adjacencyMatrix[i][j] - residualGraph[i][j];
                if (net_flow_on_edge > 0){
                    std::cout << i << " -> " << j << " | flow: " << net_flow_on_edge<< " / " << adjacencyMatrix[i][j] << "\n";
                    totalFlow += net_flow_on_edge;
                }
            }
        }
    }
    std::cout << "volume: " << totalFlow << " / " << totalCapacity << "\n";
}

void GraphAlgorithmsApp::showFlowList(neighbour** residualGraph) {
    int current_total_flow = 0;
    int totalCapacity = 0;

    // Obliczenie totalCapacity na podstawie oryginalnej neighboursList
    for (int u = 0; u < verticesNumber; u++) {
        neighbour *currentOriginal = neighboursList[u];
        while (currentOriginal != nullptr) {
            totalCapacity += currentOriginal->weight;
            currentOriginal = currentOriginal->nextVertex;
        }
    }

    std::cout << "Flow on edges (using list with R[j][i] logic):\n"; // Dodano opis dla jasności

    for (int i = 0; i < verticesNumber; i++) {
        neighbour *original_edge_iterator = neighboursList[i]; // Iterujemy po oryginalnych krawędziach z 'i'
        while (original_edge_iterator != nullptr) {
            int j_target_original = original_edge_iterator->vertex;    // Cel oryginalnej krawędzi i->j
            int original_capacity_ij = original_edge_iterator->weight; // C(i,j)

            if (original_capacity_ij > 0) { // Rozważamy tylko rzeczywiste oryginalne krawędzie
                // Potrzebujemy R(i,j) z finalResidualGraphList
                int residual_capacity_ij = 0;
                neighbour *current_edge = residualGraph[i];
                while (current_edge != nullptr) {
                    if (current_edge->vertex == j_target_original) {
                        residual_capacity_ij = current_edge->weight;
                    }
                    current_edge = current_edge->nextVertex;
                }

                int net_flow_ij = original_capacity_ij - residual_capacity_ij;

                if (net_flow_ij > 0) { // Wyświetlaj tylko, jeśli przepływ netto jest dodatni
                    std::cout << i << " -> " << j_target_original << " | flow: " << net_flow_ij
                              << " / " << original_capacity_ij << "\n";
                    current_total_flow += net_flow_ij;
                }
            }
            original_edge_iterator = original_edge_iterator->nextVertex;
        }
    }
    std::cout << "volume: " << current_total_flow << " / " << totalCapacity << "\n";
}
// struct BenchmarkResult {
//     std::map<std::string, double> results;
//
//     void add(const std::string& name, int size, int density, double time) {
//         std::ostringstream key;
//         key << name << "_" << size << "_" << density;
//         results[key.str()] = time;
//     }
//
//     void save(const std::string& filename) const {
//         std::ofstream out(filename);
//         for (const auto& [key, val] : results) {
//             out << key << " = " << val << "\n";
//         }
//         out.close();
//     }
// };

// void GraphAlgorithmsApp::runAllAlgorithmTests() {
//     const int runs = 50;
//     const std::vector<int> sizes = {80, 100, 120, 140, 170, 200, 250};
//     const std::vector<int> densities = {20, 60, 99};
//     BenchmarkResult bench;
//
//     for (int size : sizes) {
//         for (int density : densities) {
//             double total_prim_list = 0, total_prim_matrix = 0;
//             double total_kruskal_list = 0, total_kruskal_matrix = 0;
//             double total_dijkstra_list = 0, total_dijkstra_matrix = 0;
//             double total_bellman_list = 0, total_bellman_matrix = 0;
//             double total_ffdfs_list = 0, total_ffdfs_matrix = 0;
//             double total_ffbfs_list = 0, total_ffbfs_matrix = 0;
//
//             for (int i = 0; i < runs; ++i) {
//                 std::cout<<"size: "<<size<<" , density: "<<density<<" run: "<<i<<"\n";
//
//                 GraphGenerator::generateGraphForMST(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, size, density);
//                 total_prim_list += std::get<3>(MSTSolver::primsAlgorithmForList(neighboursList, verticesNumber));
//                 total_prim_matrix += std::get<3>(MSTSolver::primsAlgorithmForMatrix(adjacencyMatrix, verticesNumber));
//                 total_kruskal_list += std::get<3>(MSTSolver::kruskalsAlgorithmForList(neighboursList, verticesNumber));
//                 total_kruskal_matrix += std::get<3>(MSTSolver::kruskalsAlgorithmForMatrix(adjacencyMatrix, verticesNumber));
//
//                 GraphGenerator::generateGraphForShortestPathAndMaxFlow(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex, size, density);
//
//                 total_dijkstra_list += std::get<2>(ShortestPathSolver::dijkstrasAlgorithmForList(neighboursList, verticesNumber, startVertex));
//                 total_dijkstra_matrix += std::get<2>(ShortestPathSolver::dijkstrasAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex));
//                 total_bellman_list += std::get<2>(ShortestPathSolver::bellmanFordAlgorithmForList(neighboursList, verticesNumber, startVertex));
//                 total_bellman_matrix += std::get<2>(ShortestPathSolver::bellmanFordAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex));
//                 total_ffdfs_matrix += std::get<1>(MaximumFlowSolver::fordFulkersonDfsAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex, endVertex));
//                 total_ffdfs_list += std::get<1>(MaximumFlowSolver::fordFulkersonDfsAlgorithmForList(neighboursList, verticesNumber, startVertex, endVertex));
//                 total_ffbfs_matrix += std::get<1>(MaximumFlowSolver::fordFulkersonBfsAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex, endVertex));
//                 total_ffbfs_list += std::get<1>(MaximumFlowSolver::fordFulkersonBfsAlgorithmForList(neighboursList, verticesNumber, startVertex, endVertex));
//             }
//
//             bench.add("prim_list", size, density, total_prim_list / runs);
//             bench.add("prim_matrix", size, density, total_prim_matrix / runs);
//             bench.add("kruskal_list", size, density, total_kruskal_list / runs);
//             bench.add("kruskal_matrix", size, density, total_kruskal_matrix / runs);
//             bench.add("dijkstra_list", size, density, total_dijkstra_list / runs);
//             bench.add("dijkstra_matrix", size, density, total_dijkstra_matrix / runs);
//             bench.add("bellman_list", size, density, total_bellman_list / runs);
//             bench.add("bellman_matrix", size, density, total_bellman_matrix / runs);
//             bench.add("ffdfs_list", size, density, total_ffdfs_list / runs);
//             bench.add("ffdfs_matrix", size, density, total_ffdfs_matrix / runs);
//             bench.add("ffbfs_list", size, density, total_ffbfs_list / runs);
//             bench.add("ffbfs_matrix", size, density, total_ffbfs_matrix / runs);
//         }
//     }
//
//     bench.save("benchmark_results.txt");
// }
