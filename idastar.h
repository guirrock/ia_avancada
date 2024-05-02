#ifndef IDASTAR_H
#define IDASTAR_H

//#include "idastarnode.h"
#include <vector>
#include <unordered_set>
#include <utility> // Para std::pair
#include <algorithm> // Para std::reverse


// Função de hash para vetor de inteiros
struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        size_t hash = 0;
        for (int i : v) {
            hash ^= std::hash<int>{}(i) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};


class IDAStar {
public:
    IDAStar(const std::vector<int>& goalState);
    

    std::vector<IDAStarNode*> idaStar(const std::vector<int>& initialState);

    int getNodesExpanded() const;
    int getNodesGenerated() const;
    double getHeuristicAverage() const;
    int getStartHeuristic() const;

private:
    std::vector<int> goalState;
    int nodesExpanded;
    int nodesGenerated;
    int heuristicSum;
    int startHeuristic;

    int manhattanDistance(const std::vector<int>& state);
    std::pair<int, std::vector<IDAStarNode*>> depthLimitedSearch(
        IDAStarNode* node, int gCost, int limit,
        std::unordered_set<std::vector<int>, VectorHash>& visited);
    std::vector<IDAStarNode*> tracePath(IDAStarNode* node);
};

#endif // IDASTAR_H
