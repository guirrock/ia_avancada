#include "bfs.h"
#include "node.h"

// Construtor da classe BFS
BFS::BFS(vector<int> _initialVector, vector<int> _finalVector) {
    Node* initialNode = new Node(_initialVector, nullptr);
    nodeQueue.push(initialNode);

    finalVector = _finalVector;
    nodesCount = 0;

    visited[initialNode->initialVector] = true;
}

// Método para resolver o quebra-cabeça usando BFS
void BFS::solve() {
    vector<Node*> solution;

    while (!nodeQueue.empty()) {
        Node* currentNode = nodeQueue.front();
        nodeQueue.pop();

        // Realiza os movimentos possíveis
        currentNode->moveUp();
        currentNode->moveLeft();
        currentNode->moveRight();
        currentNode->moveDown();

        nodesCount++;

        for (auto currentChild : currentNode->children) {
            if (currentChild->initialVector == finalVector) {
                depth = traceSolution(solution, currentChild);
                return;
            }

            if (visited.count(currentChild->initialVector) == 0) {
                visited[currentChild->initialVector] = true;
                nodeQueue.push(currentChild);
            }
        }
    }
}

// Método para rastrear a solução até o nó inicial
int BFS::traceSolution(vector<Node*>& solution, Node* endNode) {
    Node* current = endNode;
    int depth = 0;

    while (current != nullptr) {
        solution.push_back(current);
        current = current->parent;
        depth++;
    }

    return depth;
}
