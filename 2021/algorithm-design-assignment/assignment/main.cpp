// IDE: Code::Blocks 20.03
// Compiler: GNU GCC Compiler

#include <iostream>
#include <chrono>
#include "HashTableC.cpp"
#include "HashTableLP.cpp"
#include "AVLTree.cpp"
#include "PriorityQueue.cpp"
using namespace std;

 /* Unicode Explanation
    [0-9] from smallest value
    [A-Z] the middle value
    [a-z] to largest value
    By ascending order, it is expected to see smallest value first and vice versa */
const char ALPHANUM[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
const char ALPHABET[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
const string SUFFIX[] = {"com", "net", "org"};

 /* Might be difficult to implement generate string based on regex without using 3rd party library
    For now simple method, this will generate string that will match the said regex
    No guarantee if all emails are unique but chances of duplicate is very extremely low (>400m permutations.. maybe more I forgot math) */
string generateUniqueEmail() {
    string str;

    for (int i = 0; i < 4; i++)
        str += ALPHANUM[rand() % (sizeof(ALPHANUM) - 1)];
    str += '.';
    for (int i = 0; i < 4; i++)
        str += ALPHANUM[rand() % (sizeof(ALPHANUM) - 1)];
    str += '@';
    for (int i = 0; i < 5; i++)
        str += ALPHABET[rand() % (sizeof(ALPHABET) - 1)];
    str += '.';
    str += SUFFIX[rand() % 3];

    return str;
}

 /* I figured it is better to make function instead of writing duplicate for each set
    Less hassle to fix/tweak stuff and less clutter overall
    Further explanation in the main program, this is just a function for repeated stuff */
void HashTableCFunc(string *arr, const int sz, string *found, string *notFound, const int searchSz) {
    HashTableC<string> ht(sz*0.9);

    // Insertion
	auto start = chrono::system_clock::now();
    for (int i = 0; i < sz; i++)
        ht.insert(arr[i]);
	auto end = chrono::system_clock::now();
	chrono::duration<double, milli> duration = end - start;
	cout << "Time taken for insertion: " << duration.count() << "ms\n";
	// cout << ht << endl; // used for debugging

	// Search (searchSz email(s) found)
	start = chrono::system_clock::now();
	for (int i = 0; i < searchSz; i++)
        if (!ht.retrieve(found[i]))
            cout << "Target not found\n"; // for debugging; shouldn't happen since found set taken directly from data set
	end = chrono::system_clock::now();
	duration = end - start;
	cout << "Time taken for search (" << searchSz << " email(s) found): " << duration.count() << "ms\n";

	// Search (searchSz email(s) not found)
	start = chrono::system_clock::now();
	for (int i = 0; i < searchSz; i++)
        if (ht.retrieve(notFound[i]))
            cout << "Target found\n"; // for debugging; very unlikely but chances of duplicate could still happen from another set
	end = chrono::system_clock::now();
	duration = end - start;
	cout << "Time taken for search (" << searchSz << " email(s) not found): " << duration.count() << "ms\n";

	return;
}

void HashTableLPFunc(string *arr, const int sz, string *found, string *notFound, const int searchSz) {
    HashTableLP<string> ht(sz*1.5);

    // Insertion
	auto start = chrono::system_clock::now();
    for (int i = 0; i < sz; i++)
        ht.insert(arr[i]);
	auto end = chrono::system_clock::now();
	chrono::duration<double, milli> duration = end - start;
	cout << "Time taken for insertion: " << duration.count() << "ms\n";
	// cout << ht << endl; // used for debugging

	// Search (searchSz email(s) found)
	start = chrono::system_clock::now();
	for (int i = 0; i < searchSz; i++)
        if (!ht.retrieve(found[i]))
            cout << "Target not found\n"; // for debugging; shouldn't happen since found set taken directly from data set
	end = chrono::system_clock::now();
	duration = end - start;
	cout << "Time taken for search (" << searchSz << " email(s) found): " << duration.count() << "ms\n";

	// Search (searchSz email(s) not found)
	start = chrono::system_clock::now();
	for (int i = 0; i < searchSz; i++)
        if (ht.retrieve(notFound[i]))
            cout << "Target found\n"; // for debugging; very unlikely but chances of duplicate could still happen from another set
	end = chrono::system_clock::now();
	duration = end - start;
	cout << "Time taken for search (" << searchSz << " email(s) not found): " << duration.count() << "ms\n";

	return;
}

void AVLTreeFunc(string *arr, const int sz, string *found, string *notFound, const int searchSz) {
    AVLTree avl;

    // Insertion
	auto start = chrono::system_clock::now();
    for (int i = 0; i < sz; i++) {
        // cout << i << " -> " << arr[i] << endl;
        avl.insert(arr[i]);
    }
	auto end = chrono::system_clock::now();
	chrono::duration<double, milli> duration = end - start;
	cout << "Time taken for insertion: " << duration.count() << "ms\n";
    // 0 - inorder
    // 1 - preorder
    // 2 - postorder
    // 3 - levelorder
    // avl.display(3);

    // Search (searchSz email(s) found)
	start = chrono::system_clock::now();
	for (int i = 0; i < searchSz; i++)
        avl.get(found[i]);
	end = chrono::system_clock::now();
	duration = end - start;
	cout << "Time taken for search (" << searchSz << " email(s) found): " << duration.count() << "ms\n";

    // Search (searchSz email(s) not found)
	start = chrono::system_clock::now();
	for (int i = 0; i < searchSz; i++)
        avl.get(notFound[i]);
	end = chrono::system_clock::now();
	duration = end - start;
	cout << "Time taken for search (" << searchSz << " email(s) not found): " << duration.count() << "ms\n";

    return;
}

void PriorityQueueFunc(string *arr, const int sz) {
    PriorityQueue<string> pq;

    // Enqueue
	auto start = chrono::system_clock::now();
    for (int i = 0; i < sz; i++)
        pq.enqueue(arr[i]);
	auto end = chrono::system_clock::now();
	chrono::duration<double, milli> duration = end - start;
	cout << "Time taken to enqueue: " << duration.count() << "ms\n";
    // pq.print();

	// Dequeue
	start = chrono::system_clock::now();
    for (int i = 0; i < sz*0.1; i++)
        pq.dequeue();
	end = chrono::system_clock::now();
	duration = end - start;
	cout << "Time taken to dequeue (10%): " << duration.count() << "ms\n";

	return;
}

// main program
int main() {
    // init
    cout << "Initialising...\n";
    const int A = 100,
              B = 100000,
              C = 500000;
    string* setA = new string[A];
    string* setB = new string[B];
    string* setC = new string[C];

    const int maxSearch = 10;
    string* foundA = new string[maxSearch];
    string* foundB = new string[maxSearch];
    string* foundC = new string[maxSearch];
    string* notA = new string[maxSearch];
    string* notB = new string[maxSearch];
    string* notC = new string[maxSearch];

    srand(time(NULL));

    // Generate and store email into data set
    cout << "Generating unique email for each data set...\n";
    for (int i = 0; i < A; i++)
        setA[i] = generateUniqueEmail();
    for (int i = 0; i < B; i++)
        setB[i] = generateUniqueEmail();
    for (int i = 0; i < C; i++)
        setC[i] = generateUniqueEmail();

    // Store found and not found set into another set
    // Takes maxSearch last element from the set
    cout << "Storing found and not found set from data set...\n";
    for (int i = 0; i < maxSearch; i++) {
        foundA[i] = setA[A-1-i];
        foundB[i] = setB[B-1-i];
        foundC[i] = setC[C-1-i];

         /* Instead of generating another unique email, i just take from existing set into different set
            As example, what found in set B may not be found in set A
            However as mentioned in generate function, it is not guaranteed to be entirely unique
            It is still possible to be found in not found set */
        notA[i] = foundC[i];
        notB[i] = foundA[i];
        notC[i] = foundB[i];
    }

     /* Program 1a - Hash Table with Chaining
        Chaining is basically stacking the object if the table is occupied
        Hash function is explained in HashTableC.cpp */
    cout << "\n\n\nProgram 1a - Hash Table with Chaining\n";

    cout << "\n  ---  Set A  ---\n";
    HashTableCFunc(setA, A, foundA, notA, maxSearch);

    cout << "\n  ---  Set B  ---\n";
    HashTableCFunc(setB, B, foundB, notB, maxSearch);

    cout << "\n  ---  Set C  ---\n";
    HashTableCFunc(setC, C, foundC, notC, maxSearch);

     /* Program 1b - Hash Table with Linear Probing
        Similar to Program 1a, but insertion and searching function is different
        Insertion checks if the table slot is empty, else move onto the next and repeat the process until it finds the empty slot
        Searching is similar to insertion, however it loops through entire table until it finds the target */
    cout << "\n\n\nProgram 1b - Hash Table with Linear Probing\n";

    cout << "\n  ---  Set A  ---\n";
    HashTableLPFunc(setA, A, foundA, notA, maxSearch);

    cout << "\n  ---  Set B  ---\n";
    HashTableLPFunc(setB, B, foundB, notB, maxSearch);

    cout << "\n  ---  Set C  ---\n";
    HashTableLPFunc(setC, C, foundC, notC, maxSearch);

     /* Program 2 - Binary Search Tree (AVL)
        brief explanation, more details in AVLTree.cpp and TreeNode.cpp
         */
    cout << "\n\n\nProgram 2 - Binary Search Tree (AVL)\n";

    cout << "\n  ---  Set A  ---\n";
    AVLTreeFunc(setA, A, foundA, notA, maxSearch);

    cout << "\n  ---  Set B  ---\n";
    AVLTreeFunc(setB, B, foundB, notB, maxSearch);

    cout << "\n  ---  Set C  ---\n";
    AVLTreeFunc(setC, C, foundC, notC, maxSearch);

     /* Program 3 - Priority Queue with Heap
        By maxheap, it will dequeue by (alphabetically) descending order [z-a][Z-A][9-0] */
    cout << "\n\n\nProgram 3 - Priority Queue with Heap\n";

    cout << "\n  ---  Set A  ---\n";
    PriorityQueueFunc(setA, A);

    cout << "\n  ---  Set B  ---\n";
    PriorityQueueFunc(setB, B);

    cout << "\n  ---  Set C  ---\n";
    PriorityQueueFunc(setC, C);

    cout << "\n\n\nEnter any key to exit...\n";
    cin.get();
    return 0;
}
