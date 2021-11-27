// Heap Sort
#include <iostream>
using namespace std;

template <typename T>
void printArray(T A[], int n) {
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
}

void heapify(int A[], int array_size, int j) {
    int max;
    int left = 2*j+1;
    int right = 2*j+2;
    if (left < array_size && A[left] > A[j])
        max = left;
    else
        max = j;

    if (right < array_size && A[right] > A[max])
        max = right;

    if (max != j) {
        swap (A[j], A[max]);
        heapify(A, array_size, max);
    }
}

void heap_sort(int A[], int array_size) {
    for (int j = (array_size-1)/2; j >= 0; j--)
        heapify(A, array_size, j);
    for (int i = array_size-1; i >= 1; i--) {
        swap(A[0], A[i]);
        heapify(A, --array_size, 0);
    }
}

int main() {
    const int n = 7;
    int A[n] = {38, 9, 38, 37, 155, 197, 65};
    cout << "Input: ";
    printArray(A, n);
    heap_sort(A, n);
    cout << "After Heap sort: ";
    printArray(A, n);
}
