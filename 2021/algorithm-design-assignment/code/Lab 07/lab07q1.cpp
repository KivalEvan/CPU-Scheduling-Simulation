#include <iostream>
using namespace std;

void printArray (int A[], int n) {
    for (int i = 0; i < n; ++i)
        cout << A[i] << ' ';
    cout << endl;
}

void merge (int A[], int Temp[], int p, int m, int r) {
    int i, j;
    for (i = m + 1; i > p; i--)
        Temp[i - 1] = A[i - 1];
    for (j = m; j < r; j++)
        Temp [r + m - j] = A[j + 1];
    // Misch-Schritt
    for (int k = p; k <= r; k++)
        if (Temp[j] < Temp [i])
            A[k] = Temp[j--];
        else
            A[k] = Temp[i++];
}

void mergesort (int A[], int Temp[], int p, int r) {
    // Put your code here!
    if (p < r) {
        // Divide: divide a into two nearly equal parts.
        int m = (p + r) / 2;
        // Recur: sort each half.
        mergesort (A, Temp, p, m);
        mergesort (A, Temp, m + 1, r);
        // Conquer: merge the two sorted halves.
        merge (A, Temp, p, m, r);
    }
}

void startMergeSort (int A[], int n) {
    int* Temp = new int[n];
    mergesort (A, Temp, 0, n-1);
    delete [] Temp;
}

int main() {
    // Put your code here!
    int arr[] = {96, 48, 91, 94, 31, 77, 2};
    printArray (arr, 7);
    startMergeSort (arr, 7);
    printArray (arr, 7);
}
