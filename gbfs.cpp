#include "gbfs.h"
#include <algorithm>

GBFS::GBFS(const std::vector<int>& finalVector)
    : finalVector(finalVector), nodesCount(0), heuristicSum(0), startHeuristic(0) {}

int GBFS::getNodesCount() const {
    return nodesCount;
}

double GBFS::getHeuristicAverage() const {
    return (nodesCount > 0) ? (heuristicSum / nodesCount) : 0.0;
}

int GBFS::getStartHeuristic() const {
    return startHeuristic;
}

int GBFS::manhattanDistance(const std::vector<int>& state, const std::vector<int>& goal) {
    int distance = 0;
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] != 0) {
            int goalPos = static_cast<int>(std::distance(goal.begin(), std::find(goal.begin(), goal.end(), state[i])));
            int rowDistance = std::abs(static_cast<int>(i / 3) - (goalPos / 3));
            int colDistance = std::abs(static_cast<int>((i % 3) - (goalPos % 3)));
            distance += rowDistance + colDistance;
        }
    }
    return distance;
}

std::vector<Node*> GBFS::tracePath(Node* node) {
    std::vector<Node*> path;
    while (node) {
        path.push_back(node);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Node*> GBFS::solve(const std::vector<int>& initialVector) {
    std::priority_queue<GBFSNode, std::vector<GBFSNode>, GBFSComparator> openList;
    std::unordered_set<std::string> closedSet;

    Node* startNode = new Node(initialVector, nullptr, 1);
    int insertionCounter = 1;

    int startGCost = 0;
    int startHCost = manhattanDistance(initialVector, finalVector);
    startHeuristic = startHCost;

    openList.push({startNode, startGCost, startHCost});

    while (!openList.empty()) {
        GBFSNode currentGBFSNode = openList.top();
        openList.pop();

        Node* currentNode = currentGBFSNode.node;

        std::string stateStr;
        for (int i : currentNode->initialVector) {
            stateStr += std::to_string(i) + ",";
        }

        if (closedSet.count(stateStr) > 0) {
            continue;
        }

        closedSet.insert(stateStr);

        if (currentNode->initialVector == finalVector) {
            return tracePath(currentNode);
        }

        nodesCount++; // Incremento de nós expandidos
        heuristicSum += currentGBFSNode.hCost;

        currentNode->moveUp(insertionCounter++);
        currentNode->moveLeft(insertionCounter++);
        currentNode->moveRight(insertionCounter++);
        currentNode->moveDown(insertionCounter++);

        for (Node* child : currentNode->children) {
            std::string childStateStr;
            for (int i : child->initialVector) {
                childStateStr += std::to_string(i) + ",";
            }

            if (closedSet.count(childStateStr) > 0) {
                continue;
            }

            int gCost = currentGBFSNode.gCost + 1;
            int hCost = manhattanDistance(child->initialVector, finalVector);

            openList.push({child, gCost, hCost});
        }
    }

    return {}; // Se nenhum caminho foi encontrado
}
