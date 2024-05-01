#ifndef BFS_H
#define BFS_H

#include <queue>
#include <map>
#include <vector>

using namespace std;

// Classe para resolver o quebra-cabeça usando BFS
class BFS {
private:
    queue<Node*> nodeQueue; // Fila para nós ainda não explorados
    map<vector<int>, bool> visited; // Mapa para estados já visitados
    vector<int> finalVector; // Estado final do quebra-cabeça

public:
    int depth; // Profundidade da solução
    int nodesCount; // Contagem de nós explorados

    // Construtor da classe BFS
    BFS(vector<int> _initialVector, vector<int> _finalVector);

    // Método para resolver o quebra-cabeça usando BFS
    void solve();

    // Rastreia a solução até o nó inicial, retorna a profundidade
    int traceSolution(vector<Node*>& solution, Node* endNode);

};

#endif // BFS_H
