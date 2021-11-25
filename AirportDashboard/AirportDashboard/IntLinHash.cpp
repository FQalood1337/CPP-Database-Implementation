#include "IntLinHash.h";


/// <summary>
/// Constructor for the Linear Integer Hash Table
/// </summary>
/// <param name="n">The Size of The Hash</param>
IntLinHash::IntLinHash(int n) {
	SIZE = n;
	table = new int[SIZE];
	for (int i = 0; i < SIZE; i++) {
		table[i] = -1;
	}
}

/// <summary>
/// Inserts an item using a linear insert,
/// which will look in subsequent buckets if the current one is filled.
/// </summary>
/// <param name="x">The item to insert into the array</param>
void IntLinHash::InsertItem(int x) {
	int index = HashFunction(x);
	int indexesProbed = 0;

	while (indexesProbed < SIZE) {
		if (table[index] == -1) {
			table[index] = x;
			
			return;
		}
		

		index = (index + 1) % SIZE;

		++indexesProbed;
	}
}

/// <summary>
/// The hashing function for the Integer Linear Hash
/// </summary>
/// <param name="x">The key</param>
/// <returns>The bucket this number belongs to</returns>
int IntLinHash::HashFunction(int x) {
	return (x % SIZE);
}

/// <summary>
/// Removes the given number from the hash table if it exists.
/// </summary>
/// <param name="key">The number we're searching for</param>
void IntLinHash::DeleteItem(int key) {
	int index = HashSearch(key);
	
	if (index != -1) {
		table[index] = -1;
	}
}


/// <summary>
/// Searches for the given key and return the index
/// </summary>
/// <param name="x">They key to search for</param>
/// <returns>If the key exists, the bucket for which it belongs</returns>
int IntLinHash::HashSearch(int x) {
	int index = HashFunction(x);
	int indexesProbed = 0;

	while (indexesProbed < SIZE) {
		if (table[index] == x) {
			return index;
		}
		index = (index + 1) % SIZE;

		++indexesProbed;
	}
	return -1;
}

/// <summary>
/// Displays the hash
/// </summary>
void IntLinHash::DisplayHash() {
	for (int i = 0; i < SIZE; i++) {
		cout << i << "---   " << table[HashFunction(i)];
		cout << endl;
	}
}

