#include "astar_functions.h" // Include the header file
#include <cmath>             // For std::sqrt and std::pow
#include <algorithm>         // For std::min_element
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>           // For std::pair
#include <iostream>

// Constructor Implementation
Astar::Astar(const std::unordered_map<std::pair<int, int>, std::vector<std::pair<int, int>>, pair_hash>& graph_,
             const std::pair<int, int>& startNode_,
             const std::pair<int, int>& goalNode_)
    : graph_(graph_), startNode_(startNode_), goalNode_(goalNode_) {
    // Precompute Euclidean distances from all nodes to the goal node
    eu_distance_ = EuDistance();
}

// Calculate Euclidean distances from all nodes to the goal node
std::unordered_map<std::pair<int, int>, double, pair_hash> Astar::EuDistance() {
    std::unordered_map<std::pair<int, int>, double, pair_hash> eu_distance;

    for (const auto& curr : graph_) {
        int xdiff = curr.first.first - goalNode_.first;
        int ydiff = curr.first.second - goalNode_.second;
        double distance = std::sqrt(std::pow(xdiff, 2) + std::pow(ydiff, 2));
        eu_distance.insert({curr.first, distance});
    }
    return eu_distance; // Return the map with all distances
}

// Calculate the actual cost between two nodes
double Astar::actual_cost(const std::pair<int, int>& currNode, const std::pair<int, int>& neighborNode) const {
    int xdiff = currNode.first - neighborNode.first;
    int ydiff = currNode.second - neighborNode.second;
    double distance = std::sqrt(std::pow(xdiff, 2) + std::pow(ydiff, 2));
    return distance;
}

// Get neighbors of a given node, excluding those in explored_set_
std::vector<std::pair<int, int>> Astar::GetNeighbors(const std::pair<int, int>& node) const {
    std::vector<std::pair<int, int>> valid_neighbors;

    auto it = graph_.find(node);
    if (it != graph_.end()) {
        for (const auto& curr : it->second) {
            // Check if the current neighbor is not in explored_set_
            if (std::find(explored_set_.begin(), explored_set_.end(), curr) == explored_set_.end()) {
                valid_neighbors.push_back(curr);
                // std::cout << "Neighbor added: (" << curr.first << ", " << curr.second << ")\n";
            } else {
                // std::cout << "Neighbor skipped (already in explored_set_): (" << curr.first << ", " << curr.second << ")\n";
            }
        }
    }
    return valid_neighbors;
}

// Calculate the total cost of a potential path
double Astar::cost(const std::pair<int, int>& possible_node) {
    double cost_tracker = 0.0;

    auto it = explored_set_.begin();
    while (it != explored_set_.end()) {
        auto current = *it; // Current element
        ++it; // Move to the next element

        if (it != explored_set_.end()) {
            auto next = *it;
            cost_tracker += actual_cost(current, next);
            // std::cout << actual_cost(current, next) << " + ";
        } else {
            auto hcost = eu_distance_.find(possible_node);
            if (hcost != eu_distance_.end()) {
                cost_tracker += hcost->second + actual_cost(current, possible_node);
                // std::cout << hcost->second << " = " << cost_tracker << std::endl;
            }
        }
    }

    return cost_tracker;
}

void Astar::optimal_path() {
    // std::cout << "Contents of eu_distance_:\n";
    // for (const auto& entry : eu_distance_) {
    //     std::cout << "Node (" << entry.first.first << ", " << entry.first.second
    //               << ") -> Distance: " << entry.second << "\n";
    // }

    bool is_active = true;
    std::unordered_set<std::pair<int, int>, pair_hash> in_frontier;

    do {
        // if (frontier_.empty()) {
        //     std::cout << "Frontier is empty.\n";
        // }

        // Initialize the explored set if it's empty
        if (explored_set_.empty()) {
            explored_set_.push_back(startNode_);
        }

        // If the current node is the goal node, terminate the loop
        if (explored_set_.back().first == goalNode_.first && explored_set_.back().second == goalNode_.second) {
            // std::cout << "Goal node reached!\n";
            is_active = false;
            break;
        }

        // std::cout << "Explored Set:\n";
        // for (const auto& element : explored_set_) {
        //     std::cout << "(" << element.first << ", " << element.second << ")\n";
        // }

        std::pair<int, int> last_element = {-1, -1};
        if (!explored_set_.empty()) {
            last_element = explored_set_.back();
            // std::cout << "Current element of explored set: (" << last_element.first << ", " << last_element.second << ")\n";
        }

        std::vector<std::pair<int, int>> neighbors = GetNeighbors(last_element);

        for (const auto& curr : neighbors) {
            // Check if the node is already in the frontier or explored
            if (std::find(explored_set_.begin(), explored_set_.end(), curr) == explored_set_.end() &&
                in_frontier.find(curr) == in_frontier.end()) {
                frontier_.push({curr, cost(curr)});
                in_frontier.insert(curr);
            }
        }

        // Add the top node in the frontier to the explored set and remove it from the frontier
        if (!frontier_.empty()) {
            auto next_node = frontier_.top().first;
            explored_set_.push_back(next_node);
            in_frontier.erase(next_node);
            frontier_.pop();
        }
    } while (is_active);
}

void Astar::print_path() const {
    if (explored_set_.empty()) {
        std::cout << "Explored set is empty.\n";
        return;
    }

    std::cout << "Explored Set (Optimal Path):\n";
    for (const auto& node : explored_set_) {
        std::cout << "(" << node.first << ", " << node.second << ")";
        if (node != explored_set_.back()) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n";
}