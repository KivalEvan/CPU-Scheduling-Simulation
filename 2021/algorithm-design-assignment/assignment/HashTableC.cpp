// HashTableC.cpp
// Hash Table using Chaining

#include <vector>
#include "LinkedList.cpp" // available at MMLS.
using namespace std;

template <typename T>
class HashTableC {
	vector<LinkedList<T>> table;
	int hashFunction(string hashItem) {
	    // Unsigned is used so it will always return as positive integer
	    int unsigned val = 0;
	     /* Internally, string is just a char array and each char is a value
            Thus it can be summed up and be returned for hash function
            For each character in string the hash function is multiplied by arbitrary prime number and added by character value
            Time complexity is O(n) */
	    for (int i = 0; i < hashItem.length(); i++)
            val = val * 11 + hashItem[i];
		return val % table.size();
	}
public:
	HashTableC(int size) {
		table.resize(size);
	}
	~HashTableC() {
	for (int i = 0; i < table.size(); i++)
		table[i].makeEmpty();
	}
	int size() {
		return table.size();
	}
	// Insertion by chaining
	void insert(T newItem) {
        int index = hashFunction(newItem);
        table[index].insertFront(newItem);
	}
	bool retrieve(T &target) {
        int index = hashFunction(target);
        return table[index].find(target);
	}
	friend ostream &operator<< (ostream &os, HashTableC<T> &ht) {
        for (int i = 0; i < ht.size(); i++)
            os << i << " = " << ht.table[i] << endl;
        return os;
	}
};
