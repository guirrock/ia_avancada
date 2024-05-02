#include "astar.h"

Astar::Astar(const std::vector<int>& finalVector)
    : finalVector(finalVector), nodesCount(0), heuristicSum(0), startHeuristic(0) {}

int Astar::getNodesCount() const {
    return nodesCount;
}

float Astar::getHeuristicAverage() const {
    return (nodesCount > 0) ? (heuristicSum / nodesCount) : 0.0f;
}

int Astar::getStartHeuristic() const {
    return startHeuristic;
}

int Astar::manhattanDistance(const std::vector<int>& state, const std::vector<int>& goal) {
    int distance = 0;
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] != 0) {
            int goalPos = static_cast<int>(std::distance(goal.begin(), std::find(goal.begin(), goal.end(), state[i])));
            int rowDistance = std::abs(static_cast<int>(i / 3) - static_cast<int>(goalPos / 3));
            int colDistance = std::abs(static_cast<int>(i % 3) - static_cast<int>(goalPos % 3));
            distance += rowDistance + colDistance;
        }
    }
    return distance;
}

std::vector<Node*> Astar::tracePath(Node* node) {
    std::vector<Node*> path;
    while (node) {
        path.push_back(node);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Node*> Astar::findSolution(const std::vector<int>& initialVector) {
    std::priority_queue<AstarNode, std::vector<AstarNode>, AstarComparator> openList;
    std::unordered_set<std::string> closedSet;
    int insertionCounter = 0;

    Node* startNode = new Node(initialVector, nullptr, insertionCounter++);
    int startGCost = 0;
    int startHCost = manhattanDistance(initialVector, finalVector);
    int startFCost = startGCost + startHCost;

    openList.push({ startNode, startGCost, startHCost, startFCost });
    startHeuristic = startHCost;

    while (!openList.empty()) {
        AstarNode currentAstarNode = openList.top();
        openList.pop();

        Node* currentNode = currentAstarNode.node;

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

        nodesCount++;
        heuristicSum += currentAstarNode.hCost;

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

            int gCost = currentAstarNode.gCost + 1;
            int hCost = manhattanDistance(child->initialVector, finalVector);
            int fCost = gCost + hCost;

            openList.push({ child, gCost, hCost, fCost });
        }
    }

    return {}; // Se nenhum caminho foi encontrado
}
