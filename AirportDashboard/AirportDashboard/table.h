#pragma once
#include "includes.h"
//#include "TableFactory.h"
#include "DataRow.h"
#include "DataColumn.h"



/// <summary>
/// This is a class which holds a vector of data rows and a vector for the primary key.
/// TODO: Create a third vector of columns with empty data which is used as a template when populating the rows.
/// </summary>
class Table{
public:

	/// <summary>
	/// Empty constructor
	/// </summary>
	Table(); 

	

	/// <summary>
	/// This takes in a vector of schema information provided by the table factory. It takes this information, parses it, and adds it to the list of data columns
	/// this effectively initiates the data bases schema and makes for a real nice way to create the data.
	/// </summary>
	/// <param name="schema"></param>
	void InitializeTableSchema(vector<string> schema);

	/// <summary>
	/// This function takes in a 2d vector of strings then uses them to populate
	/// </summary>
	/// <param name="data"></param>
	void InitializeTableData(vector<vector<string>> data);

	/// <summary>
	/// This will print the table's contents in a tabular format, should be extremely simple to do.
	/// </summary>
	void PrintTable();

	/// <summary>
	/// This function will return a string thats either padded with extra spaces or cut short depending on a given value
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	string PadString(string s, int i);

	vector<DataColumn> GetCols(); 
	vector<DataRow> GetRows(); 
	
	void AddKey(string primary_key);
	vector<string> GetKey(); 

	int HashFunction(int i);

	void InsertItem( DataRow row);

	string GetTitle();


	/// <summary>
	/// This function will check if the given key exists in the table
	/// </summary>
	/// <param name="vals"></param>
	/// <returns>row number of the row containg the key. If key not found it returns -1</returns>
	int KeyExists(vector<string>);

	/// <summary>
	/// Update a record in the table's corresponding CSV file and in the table in program's memory
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="colvals"></param>
	/// <param name="row_idx"></param>
	/// <returns></returns>
	void UpdateCsv(string, vector<string>, int);

	/// <summary>
	/// Write/Append a record in the table's corresponding CSV file and in the table in program's memory
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="colvals"></param>
	/// <returns></returns>
	void WriteToCsv(string, vector<string>);


	/// <summary>
	/// Print data corresponding to the table's row for the given row id.
	/// </summary>
	/// <param name="rowid"></param>
	/// <returns></returns>
	void PrintTableRow(int rowid);


	/// <summary>
	/// Perform SELECT Operation as per the description provided in the documnetation
	/// </summary>
	/// <param name="values"></param>
	/// <param name="table"></param>
	/// <returns></returns>
	void SELECT(string, string);

	/// <summary>
	/// Perform UPDATE Operation as per the description provided in the documnetation
	/// </summary>
	/// <param name="inputLine"></param>
	/// <param name="table"></param>
	/// <returns></returns>
	void UPDATE(string, string);

	/// <summary>
	/// Perform INSERT Operation as per the description provided in the documnetation
	/// </summary>
	/// <param name="inputLine"></param>
	/// <param name="table"></param>
	/// <returns></returns>
	void INSERT(string, string);
	
	/// <summary>
	/// Print a message on the CLI
	/// </summary>
	/// <param name="table"></param>
	/// <param name="key_tuple"></param>
	/// <param name="message"></param>
	/// <returns></returns>
	void AlertMessage(string, string, string);

private:
	/// <summary>
	/// Here is a quote from the Lab report:
	/// In each row: the first column is the name of the tables and the rest are data
	//elements.
	///▪ There is colon ‘:’ separator in each column. The key for each table
	///is defined by “k” followed by ‘:’ separator. Some tables may have
	///compound keys.
	///▪ The type of data will be either string or integer which is defined as
	///“:str” or “:int”.
	///
	/// In the real world, primary keys are the set of columns which make rows unique. Meaning that these 3 columns in each row
	/// will be a unique combination and cannot be repeated. This will be important for preventing duplicate insertions.
	/// </summary>
	vector<string> primary_key;
	/// <summary>
	/// This is a vector representing our database schema, it represents what our columns are and where in the relevant arrays within our data rows they exist
	/// </summary>
	vector<DataColumn> columns;
	vector<DataRow> rows; 

	DataRow* hashTable;


	//MyHashTable index;

	/// <summary>
	/// This is just the name of the table.
	/// </summary>
	string title;



};
