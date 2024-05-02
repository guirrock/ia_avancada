#ifndef IDFSNODE_H
#define IDFSNODE_H

#include "node.h"
#include <vector>

class IDFSNode {
public:
    Node* currentNode;
    int maxDepth;

    IDFSNode(Node* _currentNode, int _maxDepth);

    bool shouldStop() const;
};

#endif // IDFSNODE_H
