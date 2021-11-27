#include <iostream>
// 1. Include HashTable.cpp.


using namespace std;

int main() {
  const int n = 10;
  int A[n] = {36, 99, 80, 21, 58, 11, 25, 46, 91, 10};
  // 2. Declare a hashtable of int named "ht", size is 11.


  cout << "Array : ";
  for (int i = 0; i < n; i++) {
    cout << A[i] << " ";
    // 3. Insert A[i] into ht.

  }
  cout << endl;

  // Display ht.
  cout << ht << endl;

  int target;
  cout << "Target to retrieve: ";
  cin >> target;
  // 4. Retrieve the target from ht.



}
