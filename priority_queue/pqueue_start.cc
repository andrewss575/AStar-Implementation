// This is my file to learn how to code priority queue in c++

// using this include to use queues in general
// typical queues are FIF0, First In, First Out
// under the hood of queues in c++ is a vector
#include <queue>

#include<iostream>
#include<string>

int main() {
    // creating a priority queue. For ints, the default prioritizes larger
    // numbers (largest element at the top). We can change this tho
    std::priority_queue<int> pq;

    // using push add element to the queue
    pq.push(10);
    pq.push(1);
    pq.push(1000);
    pq.push(100);

    // because we are working with a priority queue, the queue will be ordered
    // so that the larger number (1000) is on the top. Let's print the top by
    // using .top() function
    std::cout << pq.top() << std::endl;
   
    // so if I were to pop for the first time, the first element popped will be 1000
    pq.pop();

    // now let's print the whole priotiy queue after popping the top element
    // the only time we can see every element in the queue is to pop it one at
    // a time and use .top() function. But when we do this, we basically remove
    // the whole pritoy queue, so we can create a temporary priority queue that
    // copies the priotiy queue we are currently using and use that to print cause we 
    // dont care if it gets erased

    //can't simply use range based for-loops or iterators on queues
    std::priority_queue<int> temp_pq = pq;
    std::cout << "The queue after popping the top element: \n";
    while (!temp_pq.empty()) {
        std::cout << temp_pq.top() << " "; // Access the top element
        temp_pq.pop(); // Remove the top element
    }
    std::cout << std::endl;
    
    // also note that priority queues have a .size() function that returns
    // number of elements in the priority queue
    return 0;
     
}
