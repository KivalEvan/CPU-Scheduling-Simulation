#include <iostream>
using namespace std;

void printArray (int A[], int n) {
    for (int i = 0; i < n; ++i)
        cout << A[i] << ' ';
    cout << endl;
}

Partition(int A[], int p, int r) {
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= A[r]) {
            i++;
		    swap (A[i], A[j]);
        }
	}
    swap (A[i+1], A[r]);
	return i + 1;
}

QuickSelect (int a[], int p, int r, int k) {
    if (p <= r) {
        int pi = Partition (a, p, r); // pivot index.
        cout << p << ' ' << r << ' ' << k << ' ' << pi << endl;
        cout << a[pi] << endl;
        printArray(a, 9);
        if (k == pi)
            return a[pi];
        if (k < pi)
            QuickSelect (a, p, pi-1, k);
        else
            QuickSelect (a, pi+1, r, k);
    }
}

int main() {
    // Put your code here!
    int arr[] = {31, 77, 4, 96, 42, 94, 55, 91, 66};
    //printArray (arr, 9);
    cout << QuickSelect (arr, 0, 8, 6) << endl;
    //printArray (arr, 9);
}
