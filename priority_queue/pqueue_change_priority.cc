// what we know about priority queues now, lets change the priorty
// by creating a custom comparator

// I want to have a queue that prioritizes numbers that are divisble by 3
// if they are both divisible by 3, prioritizes the larger number

// to do that, we have to create a struct to define the prioritzation
// a struct is like a class but the member varibales are public by default
// Custom comparator for the priority queue

// This struct compares with two different elements but when we create the priorty queue, 
// it will sort the whole queue based on the custom comparator regardless of how many
// elemnts are in the priority queue
struct CustomComparator {
    bool operator()(int a, int b) {
        // Prioritize numbers divisible by 3
        bool aDivBy3 = (a % 3 == 0);
        bool bDivBy3 = (b % 3 == 0);

        if (aDivBy3 && !bDivBy3) {
            return false; // a has higher priority
        } else if (!aDivBy3 && bDivBy3) {
            return true; // b has higher priority
        } else if (aDivBy3 && bDivBy3) {
            return a < b; // Both divisible by 3, prioritize the larger number
        } else {
            return a > b; // Neither divisible by 3, prioritize the smaller number
        }
    }
};

int main() {
    // Priority queue with custom comparator
    std::priority_queue<int, std::vector<int>, CustomComparator> pq;

    // Adding elements
    pq.push(10);
    pq.push(15);
    pq.push(6);
    pq.push(9);
    pq.push(4);
    pq.push(7);

    // Print elements in priority order
    std::cout << "Elements in custom priority order: ";
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << std::endl;

    return 0;
}