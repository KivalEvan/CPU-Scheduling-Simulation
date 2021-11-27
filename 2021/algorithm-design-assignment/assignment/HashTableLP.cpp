// HashTableLP.cpp
// Hash Table using Linear Probing

#include <vector>
#include "LinkedList.cpp" // available at MMLS.
using namespace std;

template <typename T>
class HashTableLP {
	vector<LinkedList<T>> table; // I could prolly just not use linked list and make new class for this but it works for now
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
	HashTableLP(int size) {
		table.resize(size);
	}
	~HashTableLP() {
	for (int i = 0; i < table.size(); i++)
		table[i].makeEmpty();
	}
	int size() {
		return table.size();
	}
     /* Insertion by linear probing
        Check for empty slot, if not loop through next until it finds empty slot
        Once it finds empty slot, insert the item */
	void insert(T newItem) {
        int index = hashFunction(newItem);
        while (!table[index].isEmpty()) {
            index++;
            index %= size();
        }
        table[index].insertFront(newItem);
	}
	 /* Similar method as to insertion
        Loops around the table once until it finds the target
        This is bad if the target does not exist, it will loop through entire table */
	bool retrieve(T &target) {
        int index = hashFunction(target);
        if (table[index].find(target))
            return true;
        int findIdx = (index + 1) % size();
        while (findIdx != index) {
            if (table[findIdx].find(target))
                return true;
            findIdx++;
            findIdx %= size();
        }
        return false;
	}
	friend ostream &operator<< (ostream &os, HashTableLP<T> &ht) {
        for (int i = 0; i < ht.size(); i++)
            os << i << " = " << ht.table[i] << endl;
        return os;
	}
};
