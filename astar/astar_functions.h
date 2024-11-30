#ifndef ASTAR_H
#define ASTAR_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <utility> // For std::pair

// Define the custom hash function for std::pair<int, int>
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ (std::hash<T2>()(pair.second) << 1);
    }
};

// Custom comparator for the priority queue
struct Compare {
    bool operator()(const std::pair<std::pair<int, int>, double>& a,
                    const std::pair<std::pair<int, int>, double>& b) const {
        return a.second > b.second; // Min-heap: smaller values have higher priority
    }
};

class Astar {
public:
    // Constructor
    Astar(const std::unordered_map<std::pair<int, int>, std::vector<std::pair<int, int>>, pair_hash>& graph_,
          const std::pair<int, int>& startNode_,
          const std::pair<int, int>& goalNode_);

    // Public method to find the optimal path
    void optimal_path();

    //printing the astar path
    void print_path() const;

private:
    // Private methods
    std::unordered_map<std::pair<int, int>, double, pair_hash> EuDistance(); // Updated signature
    double actual_cost(const std::pair<int, int>& currNode, const std::pair<int, int>& neighborNode) const;
    std::vector<std::pair<int, int>> GetNeighbors(const std::pair<int, int>& node) const;
    double cost(const std::pair<int, int>& possible_node);

    // Member variables
    std::unordered_map<std::pair<int, int>, std::vector<std::pair<int, int>>, pair_hash> graph_;
    std::pair<int, int> goalNode_;
    std::pair<int, int> startNode_;
    std::unordered_map<std::pair<int, int>, double, pair_hash> eu_distance_;
    std::vector<std::pair<int, int>> explored_set_;
    std::priority_queue<std::pair<std::pair<int, int>, double>, 
                        std::vector<std::pair<std::pair<int, int>, double>>, 
                        Compare> frontier_;
};

#endif // ASTAR_H
