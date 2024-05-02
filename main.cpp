#include "astar.h"
#include "gbfs.h"
#include "bfs.h"
//#include "idfs.h"
//#include "idastar.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

int main() {
    std::ifstream inputFile("input/8puzzle_instances.txt");

    if (!inputFile.is_open()) { 
        std::cerr << "Erro ao abrir o arquivo de entrada." << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::vector<int>> initialStates;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<int> initialState;
        int num;

        while (iss >> num) {
            initialState.push_back(num);
        }

        initialStates.push_back(initialState);
    }

    inputFile.close();

    std::vector<int> finalState = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    for (const auto& initialState : initialStates) {
        // A* Algorithm
        {
            Astar astar(finalState);
            auto start_time = std::chrono::high_resolution_clock::now();

            auto solutionPath = astar.findSolution(initialState);

            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();

            if (!solutionPath.empty()) {
                std::cout << "A*: "
                          << astar.getNodesCount() << ", "
                          << solutionPath.size() - 1 << ", "
                          << duration_sec << ", "
                          << astar.getHeuristicAverage() << ", "
                          << astar.getStartHeuristic() << std::endl;
            } else {
                std::cout << "A*: Nenhuma solução encontrada." << std::endl;
            }
        }

        // GBFS Algorithm
        {
            GBFS gbfs(finalState);
            auto start_time = std::chrono::high_resolution_clock::now();

            auto solutionPath = gbfs.solve(initialState);

            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();

            if (!solutionPath.empty()) {
                std::cout << "GBFS: "
                          << gbfs.getNodesCount() << ", "
                          << solutionPath.size() - 1 << ", "
                          << duration_sec << ", "
                          << gbfs.getHeuristicAverage() << ", "
                          << gbfs.getStartHeuristic() << std::endl;
            } else {
                std::cout << "GBFS: Nenhuma solução encontrada." << std::endl;
            }
        }

        // BFS Algorithm
        {
            BFS bfs(finalState);
            auto start_time = std::chrono::high_resolution_clock::now();

            auto solutionPath = bfs.solve(initialState);

            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();

            if (!solutionPath.empty()) {
                std::cout << "BFS: "
                          << bfs.getNodesCount() << ", "
                          << solutionPath.size() - 1 << ", "
                          << duration_sec << ", 0, "
                          << bfs.getSolutionDepth() << std::endl;
            } else {
                std::cout << "BFS: Nenhuma solução encontrada." << std::endl;
            }
        }
        /*
        // IDA* Algorithm
        {
            IDAStar idastar(finalState);
            auto start_time = std::chrono::high_resolution_clock::now();

            auto solutionPath = idastar.idaStar(initialState);

            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();

            if (!solutionPath.empty()) {
                std::cout << "IDA*: "
                          << idastar.getNodesExpanded() << ", "
                          << solutionPath.size() - 1 << ", "
                          << duration_sec << ", "
                          << idastar.getHeuristicAverage() << ", "
                          << idastar.getStartHeuristic() << std::endl;
            } else {
                std::cout << "IDA*: Nenhuma solução encontrada." << std::endl;
            }
        }

        // IDFS Algorithm
        {
            IDFS idfs(finalState);
            auto start_time = std::chrono::high_resolution_clock::now();

            auto solutionPath = idfs.solve(initialState);

            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();

            if (!solutionPath.empty()) {
                std::cout << "IDFS: "
                          << idfs.getNodesCount() << ", "
                          << solutionPath.size() - 1 << ", "
                          << duration_sec << ", "
                          << "0, " // Heurística
                          << idfs.getSolutionDepth() << std::endl;
            } else {
                std::cout << "IDFS: Nenhuma solução encontrada." << std::endl;
            }
        }*/
    }

    return 0;
}
