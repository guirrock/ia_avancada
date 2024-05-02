#include "idfs.h"
#include <algorithm>

IDFS::IDFS(const std::vector<int>& finalVector)
    : finalVector(finalVector), nodesCount(0), solutionDepth(0) {}

int IDFS::getNodesCount() const {
    return nodesCount;
}

int IDFS::getSolutionDepth() const {
    return solutionDepth;
}

std::vector<Node*> IDFS::traceSolution(Node* currentNode) {
    std::vector<Node*> solution;
    while (currentNode) {
        solution.push_back(currentNode);
        currentNode = currentNode->parent;
    }
    std::reverse(solution.begin(), solution.end());
    return solution;
}

std::vector<Node*> IDFS::solve(const std::vector<int>& initialVector) {
    Node* initialNode = new Node(initialVector, nullptr, 1);
    solutionDepth = 0;

    while (true) {
        int result = recursiveIDFS(initialNode, solutionDepth);
        if (result >= 0) {
            return traceSolution(initialNode);
        }
        solutionDepth++;
    }
}

int IDFS::recursiveIDFS(Node* currentNode, int depth) {
    nodesCount++;

    if (depth <= 0) {
        return -1; // Parar se a profundidade for zero ou negativa
    }

    if (currentNode->initialVector == finalVector) {
        return depth; // Objetivo encontrado
    }

    currentNode->moveUp(1);
    currentNode->moveLeft(1);
    currentNode->moveRight(1);
    currentNode->moveDown(1);

    for (Node* child : currentNode->children) {
        if (child->parent != nullptr && child->initialVector == child->parent->initialVector) {
            continue; // Evita ciclos
        }

        int result = recursiveIDFS(child, depth - 1);
        if (result >= 0) {
            return result; // Se encontrou uma solução, retorna
        }
    }

    return -1; // Não encontrou solução
}





