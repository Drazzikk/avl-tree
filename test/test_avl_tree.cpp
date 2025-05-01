#include <gtest.h>
#include "avl_tree.h"

TEST(AVLTreeTest, InitialInsertion) {
    AVLTree<int> tree;
    tree.insertValue(10);
    EXPECT_NE(tree.findValue(10), nullptr);
    EXPECT_EQ(tree.findValue(20), nullptr);
}

TEST(AVLTreeTest, MultipleInsertionsAndBalancing) {
    AVLTree<int> tree;
    tree.insertValue(30);
    tree.insertValue(20);
    tree.insertValue(10);

    auto rootNode = tree.findValue(20);
    ASSERT_NE(rootNode, nullptr);
    EXPECT_EQ(rootNode->value, 20);

    auto leftChild = tree.findValue(10);
    auto rightChild = tree.findValue(30);
    EXPECT_NE(leftChild, nullptr);
    EXPECT_NE(rightChild, nullptr);
}

TEST(AVLTreeTest, NodeRemoval) {
    AVLTree<int> tree;
    tree.insertValue(50);
    tree.insertValue(30);
    tree.insertValue(70);
    tree.insertValue(20);
    tree.insertValue(40);

    tree.removeValue(20);
    EXPECT_EQ(tree.findValue(20), nullptr);

    tree.removeValue(30);
    EXPECT_EQ(tree.findValue(30), nullptr);
    EXPECT_NE(tree.findValue(40), nullptr);
}

TEST(AVLTreeTest, ComplexBalancing) {
    AVLTree<int> tree;
    for (int value = 1; value <= 10; value++) {
        tree.insertValue(value);
    }

    auto rootNode = tree.findValue(4);
    ASSERT_NE(rootNode, nullptr);

    int leftSubtreeHeight = tree.getNodeHeight(rootNode->leftChild);
    int rightSubtreeHeight = tree.getNodeHeight(rootNode->rightChild);
    EXPECT_LE(abs(leftSubtreeHeight - rightSubtreeHeight), 1);
}

TEST(AVLTreeTest, RootNodeRemoval) {
    AVLTree<int> tree;
    tree.insertValue(50);
    tree.insertValue(30);
    tree.insertValue(70);

    tree.removeValue(50);
    EXPECT_EQ(tree.findValue(50), nullptr);
    EXPECT_NE(tree.findValue(30), nullptr);
    EXPECT_NE(tree.findValue(70), nullptr);
}

TEST(AVLTreeTest, SearchInEmptyTree) {
    AVLTree<int> emptyTree;
    EXPECT_EQ(emptyTree.findValue(10), nullptr);
}

TEST(AVLTreeTest, RemoveFromEmptyTree) {
    AVLTree<int> emptyTree;
    emptyTree.removeValue(10);
    EXPECT_EQ(emptyTree.findValue(10), nullptr);
}

TEST(AVLTreeTest, DuplicateInsertions) {
    AVLTree<int> tree;
    tree.insertValue(10);
    tree.insertValue(10);
    EXPECT_NE(tree.findValue(10), nullptr);
}

TEST(AVLTreeTest, TreeHeightCalculation) {
    AVLTree<int> tree;
    tree.insertValue(50);
    tree.insertValue(30);
    tree.insertValue(70);
    tree.insertValue(20);

    auto rootNode = tree.findValue(50);
    ASSERT_NE(rootNode, nullptr);
    EXPECT_EQ(rootNode->height, 3);
}

TEST(AVLTreeTest, RightRotationOperation) {
    AVLTree<int> tree;
    tree.insertValue(30);
    tree.insertValue(20);
    tree.insertValue(10);

    auto newRoot = tree.findValue(20);
    ASSERT_NE(newRoot, nullptr);
    EXPECT_EQ(newRoot->leftChild->value, 10);
    EXPECT_EQ(newRoot->rightChild->value, 30);
}

TEST(AVLTreeTest, LeftRotationOperation) {
    AVLTree<int> tree;
    tree.insertValue(10);
    tree.insertValue(20);
    tree.insertValue(30);

    auto newRoot = tree.findValue(20);
    ASSERT_NE(newRoot, nullptr);
    EXPECT_EQ(newRoot->leftChild->value, 10);
    EXPECT_EQ(newRoot->rightChild->value, 30);
}

TEST(AVLTreeTest, LeftRightRotationOperation) {
    AVLTree<int> tree;
    tree.insertValue(30);
    tree.insertValue(10);
    tree.insertValue(20);

    auto newRoot = tree.findValue(20);
    ASSERT_NE(newRoot, nullptr);
    EXPECT_EQ(newRoot->leftChild->value, 10);
    EXPECT_EQ(newRoot->rightChild->value, 30);
}

TEST(AVLTreeTest, RightLeftRotationOperation) {
    AVLTree<int> tree;
    tree.insertValue(10);
    tree.insertValue(30);
    tree.insertValue(20);

    auto newRoot = tree.findValue(20);
    ASSERT_NE(newRoot, nullptr);
    EXPECT_EQ(newRoot->leftChild->value, 10);
    EXPECT_EQ(newRoot->rightChild->value, 30);
}

TEST(AVLTreeTest, MixedOperationsSequence) {
    AVLTree<int> tree;
    const int maxValue = 100;

    for (int value = 0; value < maxValue; value++) {
        tree.insertValue(value);
    }

    for (int value = 0; value < maxValue; value += 2) {
        tree.removeValue(value);
    }

    for (int value = 0; value < maxValue; value++) {
        if (value % 2 == 0) {
            EXPECT_EQ(tree.findValue(value), nullptr);
        }
        else {
            EXPECT_NE(tree.findValue(value), nullptr);
        }
    }
}