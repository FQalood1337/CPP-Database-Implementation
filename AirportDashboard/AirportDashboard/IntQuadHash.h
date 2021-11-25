#include<string>
#include<list>
#include<iostream>
using namespace std;

class IntQuadHash {
private:
	int SIZE;
	int* table;
public:
	IntQuadHash(int n);

	void InsertItem(int x);

	void DeleteItem(int key);

	int HashSearch(int x);

	int HashFunction(int x);

	void DisplayHash();

};