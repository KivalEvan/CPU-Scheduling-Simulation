#include <iostream>
using namespace std;

template <typename T>
void printArray(T A[], int n) {
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
}

void selectionSort (int a[], int n) {
    for (int i = n-1; i > 0; i--) {
        // find the max element in the unsorted a[i .. n-1].
        int maxIndex = i; // assume the max is at the last of unsorted.
        // test against elements before i to find the largest.
        for (int j = 0; j < i; j++) {
            // if this element is larger, then it is the new max.
            if (a[j] > a[maxIndex])
                // found new max; remember its index.
                maxIndex = j;
        }
        // maxIndex is the index of the max element,
        // swap it with the current position.
        if (maxIndex != i)
            swap(a[i], a[maxIndex]);
    }
}

int main () {
    const int n = 7;
    int A[n] = {38, 9, 38, 37, 155, 197, 65};
    cout << "Input: ";
    printArray(A, n);
    selectionSort(A, n);
    cout << "After Selection sort: ";
    printArray(A, n);
}
