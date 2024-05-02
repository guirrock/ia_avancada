#ifndef IDASTARNODE_H
#define IDASTARNODE_H

//#include "node.h"
#include <vector>

class IDAStarNode {
public:
    std::vector<int> state; // Estado do quebra-cabeça
    Node* parent; // Nó pai
    Node* node;
    int g_Cost; // Custo do caminho
    int h_Cost; // Custo heurístico
    int f_Cost; // Soma de gCost e hCost

    IDAStarNode(std::vector<int> _state, IDAStarNode* _parent);

    void updateCosts(int g, int h);
    int findZero();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};

#endif // IDASTARNODE_H
