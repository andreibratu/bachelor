//
// Created by andreib on 06.06.2019.
//

#ifndef ASG4_BONUS_H
#define ASG4_BONUS_H

#include "../asg1/graph_c/interfaces/graph.h"

struct Node
{
    int value;
    Node* left;
    Node* right;
};

Graph reconstructTree(std::vector<int> preOrder, std::vector<int> inOrder);

#endif //ASG4_BONUS_H
