#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <unordered_set>
//this is where I start to implemeent A*

//first, I want to store the nodes in a data structure. 
//I am going to use a map where the key is a pair of the coordinates, while the value is a vector of coordinates that are the neighbors

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>

// Define the custom hash function for std::pair<int, int>
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ (std::hash<T2>()(pair.second) << 1);
    }
};

// Function to calculate the Euclidean distance from each node to the goal node
std::unordered_map<std::pair<int, int>, double, pair_hash> EuDistance(
    const std::unordered_map<std::pair<int, int>, std::vector<std::pair<int, int>>, pair_hash>& graph,
    const std::pair<int, int>& goalNode) {
    
    std::unordered_map<std::pair<int, int>, double, pair_hash> eu_distance;

    for (const auto& curr : graph) {
        int xdiff = curr.first.first - goalNode.first;
        int ydiff = curr.first.second - goalNode.second;
        double distance = std::sqrt(std::pow(xdiff, 2) + std::pow(ydiff, 2));
        eu_distance.insert({curr.first, distance});
    }
    return eu_distance; // Return the map with all distances
}

double actual_cost(std::pair<int, int> currNode, std::pair<int, int> neighborNode) {
    int xdiff = currNode.first - neighborNode.first;
    int ydiff = currNode.second - neighborNode.second;
    //might have to chnage depenidng how the front-end is
    double distance = std::sqrt(std::pow(xdiff, 2) + std::pow(ydiff, 2));
    return distance;
}


double cost(
    const std::unordered_map<std::pair<int, int>, double, pair_hash>& eu_distance,
    const std::unordered_set<std::pair<int, int>, pair_hash>& explored_set,
    const std::pair<int, int>& possible_node) {
    
    double cost_tracker = 0.0;

    // Iterator for the unordered set
    auto it = explored_set.begin();
    while (it != explored_set.end()) {
        auto current = *it; // Current element
        ++it; // Move to the next element
        
        if (it == explored_set.end()) {
            // If at the end of set, add heuristic cost
            auto hcost = eu_distance.find(possible_node);
            cost_tracker += hcost->second;
        } else {
             // If a next element exists, calculate the actual cost
            auto next = *it;
            cost_tracker += actual_cost(current, next);
        }
    }
    return cost_tracker;

}

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

    // Define the goal node
    std::pair<int, int> goalNode = {11, 3};

    // Calculate Euclidean distances from all nodes to the goal node
    std::unordered_map<std::pair<int, int>, double, pair_hash> distances = EuDistance(graph, goalNode);

    // Print the Euclidean distances
    for (const auto& entry : distances) {
        std::cout << "Node (" << entry.first.first << ", " << entry.first.second
                  << ") -> Distance to Goal: " << entry.second << "\n";
    }

    return 0;
}
