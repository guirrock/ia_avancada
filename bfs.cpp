#include "bfs.h"
#include <algorithm>

BFS::BFS(const std::vector<int>& finalVector)
    : finalVector(finalVector), nodesCount(0), solutionDepth(0) {}

int BFS::getNodesCount() const {
    return nodesCount;
}

int BFS::getSolutionDepth() const {
    return solutionDepth;
}

std::vector<Node*> BFS::traceSolution(Node* node) {
    std::vector<Node*> path;
    while (node) {
        path.push_back(node);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Node*> BFS::solve(const std::vector<int>& initialVector) {
    Node* initialNode = new Node(initialVector, nullptr, 1);
    BFSNode bfsNode(initialNode);

    std::vector<Node*> solutionPath;

    while (Node* currentNode = bfsNode.getNextNode()) {
        currentNode->moveUp(1);
        currentNode->moveLeft(1);
        currentNode->moveRight(1);
        currentNode->moveDown(1);

        nodesCount++;

        for (Node* child : currentNode->children) {
            if (child->initialVector == finalVector) {
                solutionPath = traceSolution(child);
                solutionDepth = static_cast<int>(solutionPath.size());
                return solutionPath;
            }

            if (!bfsNode.isVisited(child->initialVector)) {
                bfsNode.addNode(child);
                bfsNode.setVisited(child->initialVector);
            }
        }
    }

    return {}; // Se nenhum caminho foi encontrado
}
