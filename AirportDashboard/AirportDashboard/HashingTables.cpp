
#include "IntChainHash.h"
#include "IntLinHash.h"
#include "IntQuadHash.h"

void DisplayIntChainHash() {
    std::cout << "Hello World!\n";

    int arr[] = { 23,45,10,15,33, 16 };
    string str[] = { "Bob", "Betty", "Joshua Wilson", "Joe", "Billy" };
    //Standard way of getting length of an array in c++
    int len = sizeof(arr) / sizeof(arr[0]);

    cout << "Integer Chain Hash Table -------\n";

    IntChainHash integerChainHash(7);

    for (int i = 0; i < len; i++) {
        integerChainHash.InsertItem(arr[i]);
    }

    integerChainHash.DeleteItem(45);

    integerChainHash.DisplayHash();

    cout << "BUCKET OF INDEX 23: " << integerChainHash.HashSearch(23) << endl;
    cout << "BUCKET OF INDEX 16: " << integerChainHash.HashSearch(16) << endl;
    cout << "BUCKET OF INDEX 2: " << integerChainHash.HashSearch(2) << endl;
    cout << "---------------------------------\n";
}

void DisplayIntLinHash() {


    int arr[] = { 23,10,15,33, 16 };
    string str[] = { "Bob", "Betty", "Joshua Wilson", "Joe", "Billy" };
    //Standard way of getting length of an array in c++
    int len = sizeof(arr) / sizeof(arr[0]);

    cout << "Integer Linear Hash Table -------\n";

    IntLinHash integerLinHash(7);

    for (int i = 0; i < len; i++) {
        integerLinHash.InsertItem(arr[i]);
    }

    integerLinHash.DeleteItem(45);

    integerLinHash.DisplayHash();

    cout << "BUCKET OF INDEX 23: " << integerLinHash.HashSearch(23) << endl;
    cout << "BUCKET OF INDEX 16: " << integerLinHash.HashSearch(16) << endl;
    cout << "BUCKET OF INDEX 2: " << integerLinHash.HashSearch(2) << endl;
    cout << "---------------------------------\n";
}

void DisplayIntQuadHash() {


    int arr[] = { 23,10,45,33, 16 };
    string str[] = { "Bob", "Betty", "Joshua Wilson", "Joe", "Billy" };
    //Standard way of getting length of an array in c++
    int len = sizeof(arr) / sizeof(arr[0]);

    cout << "Integer Quad Hash Table -------\n";

    IntQuadHash integerQuadHash(7);

    for (int i = 0; i < len; i++) {
        integerQuadHash.InsertItem(arr[i]);
    }

    integerQuadHash.DeleteItem(45);

    integerQuadHash.DisplayHash();

    cout << "BUCKET OF INDEX 23: " << integerQuadHash.HashSearch(23) << endl;
    cout << "BUCKET OF INDEX 16: " << integerQuadHash.HashSearch(16) << endl;
    cout << "BUCKET OF INDEX 2: " << integerQuadHash.HashSearch(2) << endl;
    cout << "---------------------------------\n";
}

int main()
{
    DisplayIntChainHash();
    cout << "\n\n\n" << endl;
    DisplayIntLinHash();
    cout << "\n\n\n" << endl;
    DisplayIntQuadHash();

}



