#include "idfsnode.h"

IDFSNode::IDFSNode(Node* _currentNode, int _maxDepth)
    : currentNode(_currentNode), maxDepth(_maxDepth) {}

bool IDFSNode::shouldStop() const {
    return maxDepth <= 0;
}
