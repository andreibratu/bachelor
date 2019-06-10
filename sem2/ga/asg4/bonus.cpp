#include <utility>

//
// Created by andreib on 06.06.2019.
//

#include "bonus.h"
#include <algorithm>
#include <iostream>

/**
 * Auxiliary function to build the Tree from traversals
 *
 * In a preOrder sequence, leftmost element is the root of the tree.
 * So we know ‘A’ is root for given sequences.
 * By searching ‘A’ in inOrder sequence, we can find out all elements
 * on left side of ‘A’ are in left subtree and elements on right are in right subtree.
 *
 * @param preOrder The preorder traversal
 * @param inOrder The inorder traversal
 * @param inStart Left end of current subtree
 * @param inEnd Right end of current subtree
 * @return The Tree represented using Tree pointer data structure
 */
Node* buildRecursiveTree(std::vector<int> preOrder, std::vector<int> inOrder, int inStart, int inEnd)
{
    static int preIndex = 0;

    if(inStart > inEnd) return NULL;

    Node* tNode = new Node{preOrder[preIndex++], NULL, NULL};

    // Node has no children
    if(inStart == inEnd) return tNode;

    // Find the index of the node in inOrder traversal
    int inIndex = std::distance(inOrder.begin(), std::find(inOrder.begin(), inOrder.end(), tNode->value));

    tNode->left = buildRecursiveTree(preOrder, inOrder, inStart, inIndex - 1);
    tNode->right = buildRecursiveTree(preOrder, inOrder, inIndex + 1, inEnd);

    return tNode;
}

/**
 * Build Graph from Tree data structure
 * @param tree
 * @param g
 */
void buildGraphFromTree(Node* tree, Graph& g)
{
    g.add_vertex(tree->value);
    if (tree->left != nullptr)
    {
        g.add_vertex(tree->left->value);
        g.add_edge(tree->value, tree->left->value);
        buildGraphFromTree(tree->left, g);
    }

    if (tree->right != nullptr)
    {
        g.add_vertex(tree->right->value);
        g.add_edge(tree->value, tree->right->value);
        buildGraphFromTree(tree->right, g);
    }

    delete tree;
}


Graph reconstructTree(std::vector<int> preOrder, std::vector<int> inOrder)
{
    Node* tree = buildRecursiveTree(preOrder, std::move(inOrder), 0, preOrder.size()-1);
    Graph g;
    buildGraphFromTree(tree, g);
    return g;
}