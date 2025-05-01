#pragma once
#include <iostream>
using namespace std;

template <typename T>
class AVLTree {
public:
    class TreeNode {
    public:
        T value;
        int height;
        TreeNode* leftChild;
        TreeNode* rightChild;

        TreeNode(T val) {
            height = 1;
            value = val;
            leftChild = nullptr;
            rightChild = nullptr;
        }
    };

    TreeNode* rootNode = nullptr;
    int nodeCount = 0;

    void insertValue(T value) {
        rootNode = insertNode(rootNode, value);
    }

    void removeValue(T value) {
        rootNode = removeNode(rootNode, value);
    }

    TreeNode* findValue(T value) {
        return findNode(rootNode, value);
    }

    int getNodeHeight(TreeNode* node) {
        return node == nullptr ? 0 : node->height;
    }

    TreeNode* rotateRight(TreeNode* pivotNode) {
        TreeNode* newRoot = pivotNode->leftChild;
        pivotNode->leftChild = newRoot->rightChild;
        newRoot->rightChild = pivotNode;

        pivotNode->height = 1 + max(getNodeHeight(pivotNode->leftChild),
            getNodeHeight(pivotNode->rightChild));
        newRoot->height = 1 + max(getNodeHeight(newRoot->leftChild),
            getNodeHeight(newRoot->rightChild));
        return newRoot;
    }

    TreeNode* rotateLeft(TreeNode* pivotNode) {
        TreeNode* newRoot = pivotNode->rightChild;
        pivotNode->rightChild = newRoot->leftChild;
        newRoot->leftChild = pivotNode;

        pivotNode->height = 1 + max(getNodeHeight(pivotNode->leftChild),
            getNodeHeight(pivotNode->rightChild));
        newRoot->height = 1 + max(getNodeHeight(newRoot->leftChild),
            getNodeHeight(newRoot->rightChild));
        return newRoot;
    }

    TreeNode* insertNode(TreeNode* currentNode, T value) {
        if (currentNode == nullptr) {
            nodeCount++;
            return new TreeNode(value);
        }

        if (value < currentNode->value) {
            currentNode->leftChild = insertNode(currentNode->leftChild, value);
        }
        else if (value > currentNode->value) {
            currentNode->rightChild = insertNode(currentNode->rightChild, value);
        }

        currentNode->height = 1 + max(getNodeHeight(currentNode->leftChild),
            getNodeHeight(currentNode->rightChild));

        int balanceFactor = getNodeHeight(currentNode->leftChild) -
            getNodeHeight(currentNode->rightChild);

        if (balanceFactor > 1 && value < currentNode->leftChild->value) {
            return rotateRight(currentNode);
        }

        if (balanceFactor < -1 && value > currentNode->rightChild->value) {
            return rotateLeft(currentNode);
        }

        if (balanceFactor > 1 && value > currentNode->leftChild->value) {
            currentNode->leftChild = rotateLeft(currentNode->leftChild);
            return rotateRight(currentNode);
        }

        if (balanceFactor < -1 && value < currentNode->rightChild->value) {
            currentNode->rightChild = rotateRight(currentNode->rightChild);
            return rotateLeft(currentNode);
        }

        return currentNode;
    }

    TreeNode* removeNode(TreeNode* currentNode, T value) {
        if (currentNode == nullptr) return nullptr;

        if (value < currentNode->value) {
            currentNode->leftChild = removeNode(currentNode->leftChild, value);
        }
        else if (value > currentNode->value) {
            currentNode->rightChild = removeNode(currentNode->rightChild, value);
        }
        else {
            if (currentNode->rightChild == nullptr) {
                TreeNode* leftChild = currentNode->leftChild;
                delete currentNode;
                return leftChild;
            }
            else if (currentNode->leftChild == nullptr) {
                TreeNode* rightChild = currentNode->rightChild;
                delete currentNode;
                return rightChild;
            }
            else {
                TreeNode* successor = findMinNode(currentNode->rightChild);
                currentNode->value = successor->value;
                currentNode->rightChild = removeNode(currentNode->rightChild, successor->value);
            }
        }

        if (currentNode == nullptr) return currentNode;

        currentNode->height = 1 + max(getNodeHeight(currentNode->leftChild),
            getNodeHeight(currentNode->rightChild));

        int balanceFactor = getNodeHeight(currentNode->leftChild) -
            getNodeHeight(currentNode->rightChild);

        if (balanceFactor > 1) {
            if (getNodeHeight(currentNode->leftChild) >= getNodeHeight(currentNode->rightChild)) {
                return rotateRight(currentNode);
            }
            else {
                currentNode->leftChild = rotateLeft(currentNode->leftChild);
                return rotateRight(currentNode);
            }
        }

        if (balanceFactor < -1) {
            if (getNodeHeight(currentNode->rightChild) >= getNodeHeight(currentNode->leftChild)) {
                return rotateLeft(currentNode);
            }
            else {
                currentNode->rightChild = rotateRight(currentNode->rightChild);
                return rotateLeft(currentNode);
            }
        }

        return currentNode;
    }

    TreeNode* findMinNode(TreeNode* node) {
        while (node->leftChild != nullptr) {
            node = node->leftChild;
        }
        return node;
    }

    TreeNode* findNode(TreeNode* currentNode, T value) {
        if (currentNode == nullptr) return nullptr;

        if (value == currentNode->value) return currentNode;
        if (value < currentNode->value) return findNode(currentNode->leftChild, value);
        return findNode(currentNode->rightChild, value);
    }
};