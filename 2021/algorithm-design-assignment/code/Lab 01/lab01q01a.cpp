#include <iostream>
#include <chrono> // C++11
#include <cstdlib> // This line is required in Code::Blocks 13.12.
using namespace std;

int arrayMax (int A[], int n) {
	int currentMax = A[0];
	for (int i=1; i <= n-1; i++) {
	if (A[i] > currentMax)
		currentMax = A[i];
	}
	return currentMax;
}

template <typename T>
void printArray (T A[], int n) {
	for (int i = 0; i < n; i++)
        cout << A[i] << " ";
	cout << endl;
}

int main() {
	const int n = 500;
	srand (time(0));  // Init random number generator.
	int* A = new int[n];
	for (int i = 0; i < n; i++)
	A[i] = rand() % RAND_MAX; // generate randon number range 0-32767.

	cout << "Array A:\n";
	// printArray (A, n);

	auto start = chrono::system_clock::now();
	int currentMax = arrayMax (A, n);
	auto end = chrono::system_clock::now();
	chrono::duration<double> duration = end - start;

	cout << "The maximum integer in A is "
		<< currentMax << endl;
	cout << "Duration: " << duration.count() << "s\n";

	delete [] A;
}
