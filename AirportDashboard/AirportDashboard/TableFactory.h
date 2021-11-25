#include "includes.h"
#include "table.h"



/// <summary>
/// This is going to use a programming pattern called the factory pattern
/// Basically, what this is is we will use it to create out objects and initialize schema.
/// </summary>
class TableFactory {
public:
	/// <summary>
	/// Constructor for table factory
	/// </summary>
	//TableFactory();

	/// <summary>
	/// A 2d Vector of strings containing our schema data
	/// </summary>
	vector < vector <string >> schemaData; //data comes from here

	/// <summary>
	/// This will take in a table name and CSV file and create the appropriate table accordingly
	/// The reason this is a unique_ptr is so we can return derived classes from table from this method
	/// makes our job a lot easier rather than having to create a million methods to return each type of table
	/// </summary>
	/// <param name="file">The CSV file for the table's schema</param>
	/// <param name="name">The name of the table, this is going to be used to figure out what to construct.</param>
	/// <returns></returns>
	Table CreateTable(string tableName, string file);

	/// <summary>
	/// Initializes the schema from the schema file and populates the data into a 2D Vector.
	/// This is being done so we don't have to re-read the file every time we need to get schema information
	/// TODO: It might be worth it to make this a hash table
	/// </summary>
	void InitializeSchema();

	/// <summary>
	/// A debug print for printing the schema data
	/// </summary>
	void PrintSchemaData();

	/// <summary>
	/// This vector will find the appropriate schema, this returns a row from the tables_schema.csv,
	/// this is what is used to populate columns in rows within a table.
	/// </summary>
	/// <param name="table"></param>
	/// <returns></returns>
	vector<string> FindSchema(string table);

	
	/// <summary>
	/// All this does is return the data from a table CSV file as a 2D vector which tables can use to populate their data. 
	/// </summary>
	/// <param name="file"></param>
	/// <returns></returns>
	vector<vector<string>> GetTableDataFromFile(string file);

private:

};
