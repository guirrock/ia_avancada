//#include "idastar.h"
#include <limits>

IDAStar::IDAStar(const std::vector<int>& goalState)
    : goalState(goalState), nodesExpanded(0), nodesGenerated(0), heuristicSum(0), startHeuristic(0) {}

int IDAStar::getNodesExpanded() const {
    return nodesExpanded;
}

int IDAStar::getNodesGenerated() const {
    return nodesGenerated;
}

double IDAStar::getHeuristicAverage() const {
    return nodesGenerated > 0 ? static_cast<double>(heuristicSum) / nodesGenerated : 0.0;
}

int IDAStar::getStartHeuristic() const {
    return startHeuristic;
}

int IDAStar::manhattanDistance(const std::vector<int>& state) {
    int distance = 0;
    for (int i = 0; i < state.size(); i++) {
        if (state[i] != 0) {
            int goalPos = std::distance(goalState.begin(), std::find(goalState.begin(), goalState.end(), state[i]));
            int rowDistance = std::abs((i / 3) - (goalPos / 3));
            int colDistance = std::abs((i % 3) - (goalPos % 3));
            distance += rowDistance + colDistance;
        }
    }
    return distance;
}

std::pair<int, std::vector<IDAStarNode*>> IDAStar::depthLimitedSearch(
    IDAStarNode* node, int gCost, int limit,
    std::unordered_set<std::vector<int>, VectorHash>& visited) {

    nodesExpanded++;
    nodesGenerated++;
    heuristicSum += node->h_Cost;

    int hCost = manhattanDistance(node->state);
    int fCost = gCost + hCost;

    node->updateCosts(gCost, hCost);

    if (fCost > limit) {
        return {fCost, {}}; // Se o custo é maior que o limite, retorna o próximo limite
    }

    if (node->state == goalState) {
        return {std::numeric_limits<int>::max(), tracePath(node)}; // Se encontrou a solução, retorna o caminho
    }

    std::vector<IDAStarNode*> children = {
        node->moveUp(),
        node->moveLeft(),
        node->moveRight(),
        node->moveDown(),
    };

    int nextLimit = std::numeric_limits<int>::max();

    for (auto* child : children) {
        if (child == nullptr) {
            continue; // Ignora nós nulos
        }

        if (visited.find(child->state) != visited.end()) {
            continue; // Evitar ciclos
        }

        visited.insert(child->state); // Marca como visitado

        auto result = depthLimitedSearch(child, gCost + 1, limit, visited);

        if (!result.second.empty()) {
            return result; // Se encontrou solução
        }

        nextLimit = std::min(nextLimit, result.first); // Atualiza o próximo limite

        delete child; // Limpeza para evitar vazamentos de memória
    }

    return {nextLimit, {}}; // Se não encontrou solução, retorna próximo limite
}

std::vector<IDAStarNode*> tracePath(IDAStarNode* node) {
    std::vector<IDAStarNode*> path;
    while (node) {
        path.push_back(node);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<IDAStarNode*> IDAStar::idaStar(const std::vector<int>& initialState) {
    startHeuristic = manhattanDistance(initialState);

    IDAStarNode* initialNode = new IDAStarNode(initialState, nullptr);
    initialNode->h_Cost = startHeuristic;

    int limit = startHeuristic; // Limite inicial
    std::unordered_set<std::vector<int>, VectorHash> visited;
    std::vector<IDAStarNode*> solutionPath;

    while (solutionPath.empty()) {
        visited.insert(initialNode->state);

        auto result = depthLimitedSearch(initialNode, 0, limit, visited);

        if (!result.second.empty()) {
            solutionPath = result.second;
            break;
        }

        limit = result.first; // Atualiza limite para próxima iteração
    }

    return solutionPath;
}
