//#include "idastarnode.h"
#include <cmath>

IDAStarNode::IDAStarNode(std::vector<int> _state, IDAStarNode* _parent)
        : state(_state), parent(parent), g_Cost(0), h_Cost(0), f_Cost(0) {}

void IDAStarNode::updateCosts(int g, int h) {
    g_Cost = g;
    h_Cost = h;
    f_Cost = g + h;
}

int IDAStarNode::findZero() {
        for (int i = 0; i < state.size(); ++i) {
            if (state[i] == 0) {
                return i;
            }
        }
        return -1; // Se não encontrar
    }

IDAStarNode moveUp() {
     int zero_pos = findZero();
        if (zero_pos >= 3) { // Pode mover para cima
            vector<int> new_state = state;
            swap(new_state[zero_pos], new_state[zero_pos - 3]);
            return new Node(new_state, this);
        }
        return nullptr;
}

void IDAStarNode::moveDown() {
    int zPos = findZero();
    if (zPos < 6) {
        std::vector<int> temp = initialVector;
        std::swap(temp[zPos], temp[zPos + 3]);
        Node* child = new Node(temp, this);
        children.push_back(child);
    }
}

void IDAStarNode::moveLeft() {
   int zPos = findZero();
    if (zPos % 3 > 0) {
        std::vector<int> temp = initialVector;
        std::swap(temp[zPos], temp[zPos - 1]);
        Node* child = new Node(temp, this);
        children.push_back(child);
    }
}

void IDAStarNode::moveRight() {
    int zPos = findZero();
    if (zPos % 3 < 2) {
        std::vector<int> temp = initialVector;
        std::swap(temp[zPos], temp[zPos + 1]);
        Node* child = new Node(temp, this);
        children.push_back(child);
    }
}

