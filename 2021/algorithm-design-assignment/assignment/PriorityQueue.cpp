// PriorityQueue.cpp
// Priority Queue with Heap

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class PriorityQueue {
    vector<T> A;
    void heapify_enqueue(int index) {   // used in enqueue.
        // if already at root.
        if (index == 0)
            return;

        // parent index
        int parent = (index-1) / 2;
        // swap if parent is smaller
        if (A[parent] < A[index])
            swap(A[parent], A[index]);

        // recursion of the function
        heapify_enqueue(parent);
    }
    void heapify_dequeue(int index) {   // used in dequeue.
        // max index
        int max;
        // left child index
        int leftChild = 2*index + 1;
        // right child index
        int rightChild = leftChild + 1;

        // compare and find the greatest child
        if (leftChild < A.size() && A[leftChild] > A[index])
            max = leftChild;
        else
            max = index;
        if (rightChild < A.size() && A[rightChild] > A[max])
            max = rightChild;

        if (max != index) {
            swap(A[index], A[max]);
            heapify_dequeue(max);
        }
    }
public:
    void enqueue(T element) {
        A.push_back(element);
        heapify_enqueue(A.size()-1);    // start at last element.
    }
    T dequeue() {
        T removed_element = A[0];
        A[0] = A[A.size()-1];           // copy last element to root.
        A.pop_back();                   // remove last element.
        heapify_dequeue(0);             // start at root.
        return removed_element;
    }
    int size() {
        return A.size();
    }
    void print() {
        for (int i = 0; i < A.size(); i++) {
            cout << A[i] << " ";
        }
        cout << endl;
    }
};
