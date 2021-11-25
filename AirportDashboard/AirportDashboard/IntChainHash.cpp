#include "IntChainHash.h"

/// <summary>
/// Constructor for int chain hash
/// </summary>
/// <param name="n">The size of the array</param>
IntChainHash::IntChainHash(int n) {
	SIZE = n;
	table = new list<int>[SIZE];
}

/// <summary>
/// The hashing function for the Integer Chain Hash
/// </summary>
/// <param name="x">The key</param>
/// <returns>The bucket this number belongs to</returns>
int IntChainHash::HashFunction(int x) {
	return (x % SIZE);
}

/// <summary>
/// A function for inserting an item into the relevant list within the interger
/// chain hash.
/// </summary>
/// <param name="x">The number to insert</param>
void IntChainHash::InsertItem(int x) {
	int index = HashFunction(x);
	table[index].push_back(x);
}

/// <summary>
/// Removes the given number from the hash table if it exists.
/// </summary>
/// <param name="key">The number we're searching for</param>
void IntChainHash::DeleteItem(int key) {
	int index = HashFunction(key);
	list<int> ::iterator i;
	for (i = table[index].begin(); i != table[index].end(); i++) {
		if (*i == key) {
			break;
		}
	}

	if (i != table[index].end()) {
		table[index].erase(i);
	}

}

/// <summary>
/// Searches for the given key and return the index
/// </summary>
/// <param name="x">They key to search for</param>
/// <returns>If the key exists, the bucket for which it belongs</returns>
int IntChainHash::HashSearch(int x) {
	int index = HashFunction(x);
	list<int> ::iterator i;
	for (i = table[index].begin(); i != table[index].end(); i++) {
		if (*i == x) {
			return index;
		}
	}

	return -1;
}

/// <summary>
/// Displays the hash
/// </summary>
void IntChainHash::DisplayHash() {
	for (int i = 0; i < SIZE; i++) {
		cout << i;
		for (auto x : table[i])
			cout << " --> " << x;
		cout << endl;
	}
}
