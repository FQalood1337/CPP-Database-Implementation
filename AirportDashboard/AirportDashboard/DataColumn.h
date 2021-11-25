#ifndef DATACOLUMN_H
#define DATACOLUMN_H

#include "includes.h"

/// <summary>
/// This class is what gets stored into rows and contains a data type and a piece of data.
///  Since, as per Dr. Shirvani's specifications, the only kind of data types we will need are ints and
/// strings, we can store the data as a string and cast to integer whenever we get the data.
/// </summary>
class DataColumn 
{
public:

	/// <summary>
	/// Data columns are nothing more than a way to define database schema
	/// </summary>
	/// <param name="type"></param>
	/// <param name="title"></param>
	/// <param name="index"></param>
	DataColumn(string type, string title, int index);

	void SetIndex(int index);
	int GetIndex();


	void SetTitle(string title);
	string GetTitle(); 

	void SetType(string type); 
	string GetType(); 


private:
	string type;
	string title;
	int index;
}; 

#endif