#ifndef NODE_H
#define NODE_H

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Classe Node para representar estados do quebra-cabeça
class Node {
public:
    vector<Node*> children; // Filhos do nó
    vector<int> initialVector; // Vetor representando o estado do quebra-cabeça
    Node* parent; // Ponteiro para o nó pai

    // Construtor da classe Node
    Node(vector<int> _initialVector, Node* _parent);

    // Método para imprimir o estado do quebra-cabeça
    void printPuzzle();

    // Método para encontrar a posição do espaço vazio (zero)
    int findZero();

    // Métodos para mover o espaço vazio nas quatro direções possíveis
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
};

#endif // NODE_H
