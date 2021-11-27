// HashTable.cpp
#include <vector>
#include "LinkedList.cpp" // available at MMLS.

template <typename T>
class HashTable {
	vector< LinkedList<T> > table;
	int hashfunction (int hashitem) { // hash function
		return hashitem % table.size();
	}
public:
	HashTable (int size) {
		table.resize (size); // resize vector to support size elements.
	}
	~HashTable() {
	for (int i = 0; i < table.size(); i++)
		table[i].makeEmpty();
	}
	int size() {
		return table.size();
	}
	void insert (T newItem) {
        int index = hashfunction(newItem);
        table[index].insertFront(newItem);
	}
	bool retrieve (T & target) {
        int h = hashfunction(target);
        return table[h].find(target);
	}
	friend ostream& operator<< (ostream& os, HashTable<T>& ht) {
	for (int i = 0; i < ht.size(); i++)
		os << i << " = " << ht.table[i] << endl;
	return os;
	}
};
