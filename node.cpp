#include "node.h"
#include <algorithm>
#include <iostream>

// Construtor da classe Node
Node::Node(vector<int> _initialVector, Node* _parent) {
    initialVector = _initialVector;
    parent = _parent;
}

// Método para imprimir o estado do quebra-cabeça
void Node::printPuzzle() {
    int count = 0;
    for (auto i : initialVector) {
        if (count % 3 == 0) {
            cout << "\n";
        }
        cout << i << ' ';
        count++;
    }
    cout << "\n"; // Para garantir que a saída tenha uma nova linha no final
}

// Método para encontrar a posição do espaço vazio (zero)
int Node::findZero() {
    auto it = find(initialVector.begin(), initialVector.end(), 0);
    return static_cast<int>(distance(initialVector.begin(), it));
}

// Métodos para mover o espaço vazio nas quatro direções possíveis
void Node::moveUp() {
    int zeroPos = findZero();
    if (zeroPos >= 3) {
        vector<int> temp = initialVector;
        swap(temp[zeroPos], temp[zeroPos - 3]);
        Node* child = new Node(temp, this);
        children.push_back(child);
    }
}

void Node::moveDown() {
    int zeroPos = findZero();
    if (zeroPos < 6) {
        vector<int> temp = initialVector;
        swap(temp[zeroPos], temp[zeroPos + 3]);
        Node* child = new Node(temp, this);
        children.push_back(child);
    }
}

void Node::moveRight() {
    int zeroPos = findZero();
    if (zeroPos % 3 < 2) {
        vector<int> temp = initialVector;
        swap(temp[zeroPos], temp[zeroPos + 1]);
        Node* child = new Node(temp, this);
        children.push_back(child);
    }
}

void Node::moveLeft() {
    int zeroPos = findZero();
    if (zeroPos % 3 > 0) {
        vector<int> temp = initialVector;
        swap(temp[zeroPos], temp[zeroPos - 1]);
        Node* child = new Node(temp, this);
        children.push_back(child);
    }
}
