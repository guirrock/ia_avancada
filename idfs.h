#ifndef IDFS_H
#define IDFS_H

#include "idfsnode.h"
#include <vector>

class IDFS {
public:
    IDFS(const std::vector<int>& finalVector);

    std::vector<Node*> solve(const std::vector<int>& initialVector);

    int getNodesCount() const;
    int getSolutionDepth() const;

private:
    std::vector<int> finalVector;
    int nodesCount;
    int solutionDepth;

    int recursiveIDFS(Node* currentNode, int depth);
    std::vector<Node*> traceSolution(Node* node);
};

#endif // IDFS_H
