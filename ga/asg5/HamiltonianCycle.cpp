//
// Created by andreib on 25.05.2019.
//

#include <algorithm>
#include "HamiltonianCycle.h"

#define INF INT_MAX
typedef std::pair<int, int> State;
typedef std::unordered_map<State, int, boost::hash<State>> StateMap;

inline uint32_t removeVertexFromState(uint32_t state, uint32_t vertex)
{
    return (state ^ (1u<<vertex));
}

// Check if vertex has been visited by current path
inline bool isVertexInState(uint32_t state, uint32_t vertex)
{
    return (state&(1u<<vertex));
}

// Add vertex to state
inline uint32_t addVertexToState(uint32_t state, uint32_t vertex)
{
    return (state|(1u<<vertex));
}


/**
 * Find minimum Hamiltonian cycle of the graph via dynamic programming. Theta(2^N*N^2) complexity
 * Since a H. cycle visits all nodes, the starting point can be arbitrary.
 * State based dynamic programming approach is used -> at every point we hold the current `state` as a bitmask
 * @param g Graph
 * @return Cost of the cycle and the order for visiting the nodes
 * @throws If the graph is too large or no cycle exists
 */
std::pair<std::vector<int>, int> minimumHamiltonianCycle(Graph &g)
{
    uint32_t n = g.size();
    if(n > 20) throw std::exception(); // Unfeasible resource wise
    const uint32_t FINAL_STATE = ((1u << n) - 1); // Bitmask expressing that all nodes were visited
    // memo[BITMASK][CNODE] holds the minimum cost for getting to state BITMASK with CNODE as the last visited vertex
    StateMap memo{};
    StateMap precedent{};
    memo[{1, 0}] = 0; // Start from vertex 0
    // Build up minimum cost for all possible states
    for(uint32_t state = 1; state <= FINAL_STATE; state++)
    {
        for(uint32_t i = 0; i < n; i++)
        {
            if(memo.find({state, i}) == memo.end()) continue;
            for(uint32_t  j = 0; j < n; j++)
            {
                if (g.is_edge(i, j) && !isVertexInState(state, j))
                {
                    int cCost = memo[{state, i}];
                    int newState = addVertexToState(state, j);
                    int cost = g.get_edge_property(i, j);

                    if (memo.find({newState, j}) == memo.end() || memo[{newState, j}] > cCost + cost)
                    {
                        memo[{newState, j}] = memo[{state, i}] + cost;
                        precedent[{newState, j}] = i;
                    }
                }
            }
        }
    }

    int bestCost = INF;
    int precedentBest = -1;
    // Take paths that visit all nodes and attempt to form a cycle with the starting 0
    for(int i = 1; i < n; i++) if(memo.find({FINAL_STATE, i}) != memo.end() && g.is_edge(i, 0))
    {
        int pathCost = memo[{FINAL_STATE, i}];
        int edgeCost = g.get_edge_property(i, 0);
        if (bestCost > pathCost + edgeCost)
        {
            bestCost = pathCost + edgeCost;
            precedentBest = i;
        }
    }

    // No Hamiltonian cycles
    if(bestCost == INF) throw std::exception();

    std::vector<int> path;
    // Reconstruct the path
    int current = precedentBest;
    int currentState = FINAL_STATE;
    path.push_back(0);
    while(current != 0)
    {
        int aux = current;
        path.push_back(current);
        current = precedent[{currentState, current}];
        currentState = removeVertexFromState(currentState, aux);
    }
    path.push_back(0);
    std::reverse(path.begin(), path.end());

    return std::make_pair(path, bestCost);
}