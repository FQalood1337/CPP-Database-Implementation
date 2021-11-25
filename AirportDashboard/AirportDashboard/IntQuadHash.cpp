#include "IntQuadHash.h";


/// <summary>
/// Constructor for the Quad Integer Hash Table
/// </summary>
/// <param name="n">The Size of The Hash</param>
IntQuadHash::IntQuadHash(int n) {
	SIZE = n;
	table = new int[SIZE];
	for (int i = 0; i < SIZE; i++) {
		table[i] = -1;
	}
}

/// <summary>
/// Inserts an item using a quadratic insert,
/// </summary>
/// <param name="x">The item to insert into the array</param>
void IntQuadHash::InsertItem(int x) {
	int i = 0;
	int indexesProbed = 0;
	int index = HashFunction(x);

	while (indexesProbed < SIZE) {
		if (table[index] == -1) {
			table[index] = x;
			return;
		}
		int c1 = 1;
		int c2 = 1;
		i++;

		index = (HashFunction(x) + c1 * i + c2 *i * i) % SIZE;
		
		indexesProbed++;
	}
}

/// <summary>
/// The hashing function for the Integer Quad Hash
/// </summary>
/// <param name="x">The key</param>
/// <returns>The bucket this number belongs to</returns>
int IntQuadHash::HashFunction(int x) {
	return (x % SIZE);
}

/// <summary>
/// Removes the given number from the hash table if it exists.
/// </summary>
/// <param name="key">The number we're searching for</param>
void IntQuadHash::DeleteItem(int key) {
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
int IntQuadHash::HashSearch(int x) {
	int index = HashFunction(x);
	int indexesProbed = 0;
	int i = 0;

	while (indexesProbed < SIZE) {
		if (table[index] == x) {
			return index;
		}

		int c1 = 1;
		int c2 = 1;
		i++;
		
 		index = (HashFunction(x) + c1 * i + c2 * i * i) % SIZE;

		++indexesProbed;
	}
	return -1;
}

/// <summary>
/// Displays the hash
/// </summary>
void IntQuadHash::DisplayHash() {
	for (int i = 0; i < SIZE; i++) {
		cout << i << "---   " << table[HashFunction(i)];
		cout << endl;
	}
}

