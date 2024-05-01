#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>
#include "node.h"
#include "bfs.h"
//#include "gbfs.h"
//#include "astar.h"
//#include "idfs.h"
//#include "idastar.h"

using namespace std;

// Função para calcular a distância de Manhattan entre estados
int manhattanDistance(const vector<int>& state, const vector<int>& goal) {
    int distance = 0;
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] != 0) {
            int goalPos = std::find(goal.begin(), goal.end(), state[i]) - goal.begin();
            int rowDistance = abs(static_cast<int>(i / 3) - static_cast<int>(goalPos / 3));
            int colDistance = abs(static_cast<int>(i % 3 - goalPos % 3));
            distance += rowDistance + colDistance;
        }
    }
    return distance;
}

// Função principal para processar argumentos e executar algoritmo selecionado
int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Erro: parâmetros insuficientes. Uso: <algoritmo> [estados_iniciais]" << endl;
        return 1;
    }

    string algorithm = argv[1]; // Algoritmo a ser usado
    vector<vector<int>> initialStates; // Estados iniciais do quebra-cabeça

    // Verificar se há estados iniciais passados como argumento
    if (argc > 2) {
        istringstream iss(argv[2]);
        std::vector<int> initialState;
        int num;

        while (iss >> num) {
            initialStates.push_back(initialState);
        }

        initialStates.push_back(initialState); // Adicionar o estado lido
    } else {
        // Ler do arquivo de entrada
        string filePath;
        if (algorithm == "-astar15") {
            filePath = "input/15puzzle_instances.txt"; // Arquivo para o 15-puzzle
        } else {
            filePath = "input/8puzzle_instances.txt"; // Arquivo para o 8-puzzle
        }

        ifstream inputFile(filePath);
        if (!inputFile.is_open()) {
            cerr << "Erro ao abrir o arquivo de entrada: " << filePath << endl;
            return 1;
        }

        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            vector<int> initialState;
            int num;

            while (iss >> num) {
                initialState.push_back(num);
            }

            initialStates.push_back(initialState); // Adicionar cada estado lido
        }

        inputFile.close();
    }

    // Selecionar e executar o algoritmo apropriado
    vector<int> finalVector_8 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> finalVector_15 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    if (algorithm == "-bfs") {
        for (const auto& initialState : initialStates) {
            auto start_time = chrono::high_resolution_clock::now();
            
            BFS bfs(initialState, finalVector_8);

            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration<double>(end_time - start_time).count();

            cout << "BFS: " << bfs.nodesCount 
                << ", Profundidade: " << bfs.depth - 1 
                << ", Tempo de Execução: " << duration 
                << ", Heurística Inicial: " << manhattanDistance(initialState, finalVector_8) 
                << endl;
        }
    }/* else if (algorithm == "-gbfs") {
        for (const auto& initialState : initialStates) {
            auto start_time = chrono::high_resolution_clock::now();
            
            GBFS gbfs(initialState, finalVector_8);

            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration<double>(end_time - start_time).count();

            cout << "GBFS: " << gbfs.nodesCount 
                << ", Tempo de Execução: " << duration 
                << ", Heurística Média: " << gbfs.heuristicSum / gbfs.nodesCount 
                << ", Heurística Inicial: " << manhattanDistance(initialState, finalVector_8) 
                << endl;
        }
    } else if (algorithm == "-astar") {
        for (const auto& initialState : initialStates) {
            auto start_time = chrono::high_resolution_clock::now();
            
            Astar astar(initialState, finalVector_8);

            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration<double>(end_time - start_time).count();

            cout << "A*: " << astar.nodesCount 
                << ", Tempo de Execução: " << duration 
                << ", Heurística Média: " << astar.heuristicSum / astar.nodesCount 
                << ", Heurística Inicial: " << manhattanDistance(initialState, finalVector_8) 
                << endl;
        }
    } else if (algorithm == "-idfs") {
        for (const auto& initialState : initialStates) {
            auto start_time = chrono::high_resolution_clock::now();
            
            IDFS idfs(initialState, finalVector_8);

            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration<double>(end_time - start_time).count();

            cout << "IDFS: " << idfs.nodesCount 
                << ", Profundidade: " << idfs.depth 
                << ", Tempo de Execução: " << duration 
                << ", Heurística Inicial: " << manhattanDistance(initialState, finalVector_8) 
                << endl;
        }
    } else if (algorithm == "-idastar") {
        for (const auto& initialState : initialStates) {
            auto start_time = chrono::high_resolution_clock::now();
            
            IDAStar idastar(initialState, finalVector_8);

            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration<double>(end_time - start_time).count();

            cout << "IDA*: " << idastar.nodesCount 
                << ", Tempo de Execução: " << duration 
                << ", Heurística Inicial: " << manhattanDistance(initialState, finalVector_8) 
                << endl;
        }
    } else if (algorithm == "-astar15") {
        for (const auto& initialState : initialStates) {
            auto start_time = chrono::high_resolution_clock::now();
            
            Astar astar(initialState, finalVector_15);

            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration<double>(end_time - start_time).count();

            cout << "A* (15-puzzle): " << astar.nodesCount 
                << ", Tempo de Execução: " << duration 
                << ", Heurística Inicial: " << manhattanDistance(initialState, finalVector_15) 
                << endl;
        }
    }*/ else {
        cerr << "Algoritmo desconhecido: " << algorithm << endl;
    }

    return 0;
}
