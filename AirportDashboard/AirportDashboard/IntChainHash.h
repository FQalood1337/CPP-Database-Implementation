#include<string>
#include<list>
#include<iostream>
using namespace std;

class IntChainHash {
private:
	int SIZE;
	list<int>* table;
public:
	IntChainHash(int n);

	void InsertItem(int x);

	void DeleteItem(int key);

	int HashSearch(int x);

	int HashFunction(int x);

	void DisplayHash();

};