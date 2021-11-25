#pragma once
#include "includes.h"

using namespace std;

/// <summary>
/// This is a class which will hold a hash of columns
/// </summary>
class DataRow
{

private:
	


public:
  DataRow();
  DataRow(const DataRow &src);
  vector<string> strs;
  vector<int> ints;
 
  int id;

};
