#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void printArray (T A[], int n) {
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
}

template <typename T>
class PriorityQueue {
    vector<T> A;
    void heapify_enqueue (int index) {   // used in enqueue.
        if (index == 0)                    // if already at root.
            return;
        // parent index
        int parent = (index-1) / 2;
        // swap if parent is smaller
        if (A[parent] < A[index])
            swap (A[parent], A[index]);
        // recursion of the function
        heapify_enqueue (parent);
    }
    void heapify_dequeue (int index) {   // used in dequeue.
        int max;                           // max index
        // left child index
        int left_child = 2*index + 1;
        // right child index
        int right_child = left_child + 1;
        // compare and find the greatest child
        if (left_child >= A.size())
            max = index;
        else if (A[left_child] < A[right_child])
            max = right_child;
        else
            max = left_child;

        if (max != index) {
            swap (A[index], A[max]);
            heapify_dequeue (max);
        }
    }
public:
    void enqueue (T element) {
        A.push_back (element);
        heapify_enqueue (A.size()-1);  // start at last element.
    }
    T dequeue() {
        T removed_element = A[0];
        A[0] = A[A.size()-1];          // copy last element to root.
        A.pop_back();                  // remove last element.
        heapify_dequeue (0);           // start at root.
        return removed_element;
    }
    int size() {
        return A.size();
    }
    void print() {
        for (int i = 0; i < A.size(); i++)
            cout << A[i] << " ";
        cout << endl;
    }
};

int main () {
    int A[] = {4, 2, 5, 8, 6, 9, 3, 7};
    int n = sizeof(A)/sizeof(A[0]);
    cout << "Array = ";
    printArray (A, n);

    cout << "\nEnqueue\t: PriorityQueue\n";
    PriorityQueue<int> pq;
    for (int i = 0; i < n; i++) {
        cout << A[i] << "\t: ";
        pq.enqueue (A[i]);
        pq.print();
    }

    cout << "\nDequeue\t: PriorityQueue\n";
    for (int i = 0; i < n; i++) {
        cout << pq.dequeue() << "\t: ";
        pq.print();
    }
}
