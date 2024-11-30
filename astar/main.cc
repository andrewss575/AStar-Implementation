#include "astar_functions.h" // Include the header file
#include <cmath>   // For std::sqrt and std::pow
#include <algorithm> // For std::min_element
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <utility> // For std::pair
#include <iostream>

int main() {
    // Map to store the graph
    // Key: pair<int, int> (coordinates of the node)
    // Value: vector<pair<int, int>> (coordinates of neighbors)
    std::unordered_map<std::pair<int, int>, std::vector<std::pair<int, int>>, pair_hash> graph = {
        {{1, 10}, {{2, 12}, {1, 7}, {3, 9}}},
        {{2, 13}, {{3, 9}, {2, 12}}},
        {{2, 12}, {{2, 13}, {1, 10}}},
        {{3, 9},  {{1, 10}, {2, 13}, {4, 7}, {5, 9}}},
        {{1, 7},  {{1, 10}, {3, 6}}},
        {{3, 6},  {{1, 7}, {3, 5}}},
        {{3, 5},  {{3, 6}, {3, 3}}},
        {{3, 3},  {{3, 5}, {4, 3}}},
        {{4, 3},  {{3, 3}, {7, 2}, {5, 6}}},
        {{7, 2},  {{4, 3}, {7, 3}}},
        {{4, 7},  {{3, 9}, {5, 6}}},
        {{5, 6},  {{4, 7}, {5, 9}, {4, 3}}},
        {{5, 9},  {{5, 6}, {7, 3}, {3, 9}}},
        {{7, 12}, {{8, 11}}},
        {{8, 11}, {{9, 9}}},
        {{9, 9},  {{10, 5}}},
        {{10, 5}, {{8, 4}, {11, 3}}},
        {{11, 3}, {{10, 5}}},
        {{8, 4},  {{7, 3}, {10, 5}}},
        {{7, 3},  {{8, 4}, {5, 9}, {7, 2}}}
    };

    std::pair<int, int> startNode = {5,6};
    // Define the goal node
    std::pair<int, int> goalNode = {11, 3};
    
    //std::cout << "process begins" << std::endl;

    Astar as1{graph, startNode, goalNode};
    
    as1.optimal_path();
    
    as1.print_path();
    
    return 0;
}
