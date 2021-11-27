#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;

void partialSum (int A[], int S[], int n) {
    S[0] = A[0];
    for (int i=1; i <= n-1; i++) {
        S[i] = A[0];
        for (int j=1; j <= i; j++) {
            S[i] = S[i] + A[j];
        }
    }
}

template <typename T>
void printArray (T A[], int n) {
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
}

int main() {
	const int n = 5000000;
	int* A = new int[n] {11, 23, 5, 27, 33, 1, 45, 18};
	int* S = new int[n];
	// 3. Take start time.
	auto start = chrono::system_clock::now();
	// 4. Call partialSum.
	partialSum (A, S, n);
	// 5. Take end time.
	auto end = chrono::system_clock::now();
	// 6. Calculate duration.
	chrono::duration<double> duration = end - start;

	cout << "A:\n";
	// printArray (A, n);
	cout << "Partial sum S:\n";
	// printArray (S, n);

	// 7. Display duration.
	cout << "Duration: " << duration.count() << "s\n";

	delete [] A;
	delete [] S;
}
