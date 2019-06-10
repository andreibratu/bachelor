#include <utility>

//
// Created by andreib on 26.04.2019.
//

#include "MinCostWalk.h"
#include <limits.h>
#include <vector>
#include <iostream>
#include "../asg1/graph_c/interfaces/graph.h"

typedef std::vector<std::vector<int>> Matrix;

void squareMatrix(Matrix& costs, Matrix& transition)
{
    int n = costs.size();

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < n; k++)
            {
                if (
                    ((i == j) || (k == j) || (i == k)) ||
                    (costs[i][k] == INT_MAX || costs[k][j] == INT_MAX)
                )
                {
                    continue;
                }

                if(costs[i][j] > costs[i][k]+costs[k][j])
                {
                    transition[i][j] = k;
                    costs[i][j] = costs[i][k]+costs[k][j];
                }
            }
        }
    }
}

std::vector<int> reconstructPath(Matrix& transition, int source, int destination)
{
    std::vector<int> answer;
    while (source != destination)
    {
        answer.push_back(destination);
        if(transition[source][destination] == -1) destination = source;
        else destination = transition[source][destination];
    }
    answer.push_back(source);

    return answer;
}

std::pair<std::vector<int>, int> matrixMultiplicationMinWalk(Graph &g, int source, int destination)
{
    if(source == destination) return {{}, 0};

    int n = g.size();
    Matrix costs(n, std::vector<int>(n, 0));
    Matrix transition(n, std::vector<int>(n, -1));
    for(int i = 0; i < g.size(); i++)
    {
        for(int j = 0; j < g.size(); j++)
        {
            if(i == j)
            {
                costs[i][j] = 0;
                continue;
            }
            try
            {
                costs[i][j] = g.get_edge_property(i, j);
            }
            catch (std::exception&)
            {
                // Edge does not exist
                costs[i][j] = INT_MAX;
            }
        }
    }

    for(int i = 1; i < n; i*=2) squareMatrix(costs, transition);

    Matrix negativeCostCheck(costs);
    Matrix negativeTransitionCheck(transition);

    // If the graph has a negative cycle costs could be infinitely improved
    // Run on more iteration and check
    squareMatrix(negativeCostCheck, negativeTransitionCheck);
    for(int i = 0; i < n; i++)
    {
        if(costs[i][i] < 0)
        {
            throw std::exception();
        }
    }

    std::vector<int> path = reconstructPath(transition, source, destination);
    return {path, costs[source][destination]};
}