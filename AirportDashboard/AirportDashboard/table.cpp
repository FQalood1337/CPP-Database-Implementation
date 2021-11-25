#include "includes.h"
#include "TableFactory.h"
#include "table.h"
#include "DataColumn.h"

using namespace std; 


Table::Table() {
	hashTable = new DataRow[23];
}

string Table::GetTitle()
{
	return this->title;
}



void Table::InitializeTableSchema(vector<string> schema) {
	//Keep two integers for the indices in the vectors on the data row class
	int strIndex = 0;
	int intIndex = 0;

	//First, we are going to go over the schema, create a data column and push it to our column vectors.
	//The reason we don't need to make this a pointer or worry about the new key word is push_back on vector
	//Will create copy automatically. We also add these to our primary key.
	for (int i = 0; i < schema.size(); i++) {
		//Store the current piece of 'schema' into a temporary string
		string str = schema[i];

		//Since the first item in the schema vector is the tables title, we can just set it based on the incoming vector
		if (i == 0) {
			this->title = str;
		}
		else {
			//This is where the magic happens, we're going to get a string like this "ID:k:int" or this "Maker::str", and parse it into a
			//data column and push it to the columns vector. If it contains a :k: we will also push the title of that column to the primary_key
			//we are also going to keep track of the number of strings and ints so that we can set the desired index for the eventual vectors
			//in our datarow class.

			//Store the title of the column to a string by substringing it
			string title = str.substr(0, str.find_first_of(":"));

			//Now we can get the type pretty easy using basically the same method, excpept with the last instance of :
			string type = str.substr(str.find_last_of(":") + 1, str.length() - str.find_last_of(":"));

			//This is basically how we find if this row is a primary key or not, extremely simple way to check and we're just adding it to our primary key vector
			if (str.find(":k:") != -1) {
				primary_key.push_back(title);
			}

			//Bellow is where we finally add the columns to the column vector, an extremely simple operation and since columns is a vector we don't need to mess
			//with pointers since push back will create a copy of the data column

			//If our type is a string, increment the str index
			if (type.compare("str") == 0) {
				//cout << "COLUMN TITLE: '" << title << "' COLUMN TYPE: '" << type << "'" << "\tSTR INDEX: " << strIndex << endl;
				DataColumn d(type, title, strIndex);
				columns.push_back(d);
				strIndex++;
			}

			//If our type is an int, increment the integer index
			if (type.compare("int") == 0) {
				//cout << "COLUMN TITLE: '" << title << "' COLUMN TYPE: '" << type << "'" << "\tINT INDEX: " << intIndex << endl;
				DataColumn d(type, title, intIndex);
				columns.push_back(d);
				intIndex++;
			}
		}

	}
}

string Table::PadString(string s, int i) {
	if (s.length() < i) {
		s.append(i - s.length(), ' ');
	}

	if (s.length() > (i - 1)) {
		s = s.substr(0, i);
	}

	return s;

}

void Table::PrintTable() {
	cout << "TABLE: " << title << endl << endl;

	for (int i = 0; i < columns.size(); i++) {
		//Lets do a little extra formatting to make sure it looks real nice
		string s = columns.at(i).GetTitle();
		cout << "|" << PadString(s, 15) << "|";
	}

	cout << endl;

	for (int j = 0; j < rows.size(); j++) {
		DataRow d = rows.at(j);
		for (int k = 0; k < columns.size(); k++) {
			DataColumn c = columns.at(k);
			if (c.GetType().compare("str") == 0) {
				cout << "|" << PadString(d.strs.at(c.GetIndex()), 15) << "|";
			}

			if (c.GetType().compare("int") == 0) {
				string num = to_string(d.ints.at(c.GetIndex()));
				cout << "|" << PadString(num, 15) << "|";
			}
		}
		cout << endl;

	}

	cout << endl << endl << endl << endl;
}

void Table::InitializeTableData(vector<vector<string>> data) {
	//First we iterate through the given data file
	for (int i = 0; i < data.size(); i++) {
		//Then we loop over the inviddual items in the columns
		//Instantiate a data row
		DataRow row;

		//A temporary variable for if we can push or not
		bool b = false;

		for (int j = 0; j < data.at(i).size(); j++) {
			//We don't use the first row since it contains column headers
			if (i != 0) {
				//Set b to true so we don't push an empty row, this is the wrong way to do it, but whatever.
				b = true;

				//Storing index for fun
				int index = j;
				//Get the relevant datacolumn at our position in the row
				DataColumn d = columns.at(j);
				//Get that data columns type
				string type = d.GetType();
				
				//Get the invidual item in the row
				string item = data.at(i).at(j);

				//If this columns type is a string, push it to the rows string vector
				if (type.compare("str") == 0) {
					row.id = j + 1;
					row.strs.push_back(item);
				}

				//Otherwise, if it is an int, push it to the rows integer vector
				if (type.compare("int") == 0) {
					int itemInt = stoi(item);
					row.id = j + 1;
					row.ints.push_back(itemInt);
				}
			}
		}

		//If the row we want to push isn't empty.
		if (b) {
			//Temporarily pushing this to a rows vector. 
			rows.push_back(row);
			InsertItem(row);
		}

	}
}

int Table::HashFunction(int i) {
	return i % 23;
}

void Table::InsertItem(DataRow row) {
	int index = HashFunction(row.id);
	int indexesProbed = 0;

	while (indexesProbed < 23) {
		if (hashTable[index].id == -1) {
			hashTable[index] = DataRow(row);
			return;
		}

		index = (index + 1) % 23;
		++indexesProbed;
	}
}



vector<DataColumn> Table::GetCols()
{
	return this->columns; 
}

vector<DataRow> Table::GetRows()
{
	return this->rows; 
}

void Table::AddKey(string primary_key)
{
	this->primary_key.push_back(primary_key);
}

vector<string> Table::GetKey()
{
	return this->primary_key; 
}

int Table::KeyExists(vector<string> vals) {
	int match_count = 0;
	for (int i = 0;i < rows.size();i++)
	{
		DataRow d = rows.at(i);

		for (int j = 0; j < primary_key.size(); j++) {
			for (int k = 0; k < columns.size(); k++) {
				DataColumn c = columns.at(k);
				if (c.GetType().compare("str") == 0) {
					if (d.strs.at(c.GetIndex()) == vals.at(j))
					{
						match_count++;
					}
				}

				if (c.GetType().compare("int") == 0) {
					string num = to_string(d.ints.at(c.GetIndex()));
					if (num == vals.at(j))
					{
						match_count++;
					}
				}
			}
		}
		if (match_count < primary_key.size())
		{
			match_count = 0;
		}
		else
		{
			return i;
		}
	}
	return -1;
}

void Table::UpdateCsv(string filename, vector<string> colvals, int row_idx)
{
	vector<string> records;
	fstream fin;
	ofstream fout;
	//A string representing a line of input, used for parsing over the input file
	string inputLine;

	//column names stored in file records vector
	for (int i = 0;i < columns.size();i++)
	{
		inputLine += columns.at(i).GetTitle();
		inputLine += ",";
	}
	inputLine = inputLine.substr(0, inputLine.find_last_of(","));
	records.push_back(inputLine);

	//Attempt tp open the file;
	fin.open(filename, ios::in);

	//If file fails to load, prompt again until proper file given
	if (fin.fail())
	{
		while (fin.fail())
		{
			std::cout << "Error in opening fin while updating record." << std::endl;
			std::cout << "Try again.\n";

			std::cin >> filename;
			fin.open(filename);
		}
	}


	int counter = 0;
	do {
		//updated record values stored in file records vector
		if (counter == row_idx)
		{
			inputLine = "";
			for (int i = 0;i < colvals.size();i++)
			{
				inputLine += records.at(i);
				inputLine += ",";
			}
			inputLine = inputLine.substr(0, inputLine.find_last_of(","));
		}
		else
		{
			//Get the current line
			getline(fin, inputLine);
		}

		//If this is the empty space between the first set of lines and the queries, ignore it and break the loop.
		if (inputLine == "") {
			break;
		}

		records.push_back(inputLine);

	} while (inputLine != "");

	for (int k = 0;k < records.size();k++)
	{
		fout << records.at(k) << endl;
	}
}

void Table::WriteToCsv(string filename, vector<string> colvals)
{
	ofstream file;
	file.open(filename, std::ios_base::app);
	for (int i = 0;i < colvals.size();i++)
	{
		if (i == colvals.size() - 1)
		{
			file << colvals.at(i) << endl;
		}
		else
		{
			file << colvals.at(i) << ",";
		}
	}
	file.close();
}

void Table::AlertMessage(string table, string key_tuple, string message)
{
	cout << message << endl;
	cout << "Table :"<< table << endl;
	cout << key_tuple << endl;
}

void Table::PrintTableRow(int rowid)
{
	DataRow d = rows.at(rowid);
	for (int k = 0; k < columns.size(); k++) {
		DataColumn c = columns.at(k);
		if (c.GetType().compare("str") == 0) {
			cout << "|" << PadString(d.strs.at(c.GetIndex()), 15) << "|";
		}

		if (c.GetType().compare("int") == 0) {
			string num = to_string(d.ints.at(c.GetIndex()));
			cout << "|" << PadString(num, 15) << "|";
		}
	}
	cout << endl;
}

void Table::INSERT(string inputLine, string table)
{
	string values = inputLine.substr(inputLine.find("(") + 2, inputLine.find_last_of(",") - inputLine.find("(") - 3);
	//cout << "\nInserting data to " << table;
	values += ",";

	stringstream ss(values);

	string colval;

	vector<string> colvals;

	DataRow row;

	//to keep count of number of col values.
	int count = 0;

	//A temporary variable for if we can insert or not
	bool b = false;

	//Delimit the list of commas to get the words and push them to the words vector
	while (getline(ss, colval, ',')) {
		if (colval != "") {
			colvals.push_back(colval);
		}
		else {
			colvals.push_back("-1");
		}
	}

	//if colvals more than columns then terminate insert
	if (colvals.size() > columns.size())
	{
		AlertMessage(table, inputLine, "\nprovided # of column values is greater than number of columns of table");
		return;
	}

	while (colvals.size() < columns.size())
	{
		colvals.push_back("");
	}

	if (KeyExists(colvals)>-1)
	{
		AlertMessage(table, inputLine, "\nEntered key already exists in the table\n");
		return;
		/*cout << "\nEntered key already exists in the table\n";
		cout << "Key: \t";
		for (int c = 0;c < colvals.size(); c++)
		{
			cout << colvals.at(c)<<"\t";
		}*/
	}

	for (int i=0; i<columns.size(); i++)
	{
		DataColumn d = columns.at(i);
		//Get that data columns type
		string type = d.GetType();

		string item;
		//Get the invidual item in the row
		if (i < colvals.size())
		{
			item = colvals.at(i);
		}
		else
		{
			item = "-1";
		}

		//If this columns type is a string, push it to the rows string vector
		if (type.compare("str") == 0) {
			row.id = i + 1;
			row.strs.push_back(item);
			count++;
		}

		//Otherwise, if it is an int, push it to the rows integer vector
		if (type.compare("int") == 0) {
			int itemInt = stoi(item);
			row.id = i + 1;
			row.ints.push_back(itemInt);
			count++;
		}
	}

	if (count == columns.size())
	{
		rows.push_back(row);
		InsertItem(row);
		string filename = "data\\DATA_" + table + ".CSV";
		WriteToCsv(filename, colvals);
		AlertMessage(table, inputLine, "Data Inserted successfully");
		return;
	}
	else
	{
		AlertMessage(table, inputLine, "\nColumns mismatched\n");
	}
}

void Table::UPDATE(string inputLine, string table)
{
	string values = inputLine.substr(inputLine.find("(") + 2, inputLine.find_last_of(",") - inputLine.find("(") - 3);

	cout << "\nupdating data in " << table;
	values += ",";

	stringstream ss(values);

	string colval;

	vector<string> colvals;

	DataRow row;

	//to keep count of number of col values.
	int count = 0;

	//A temporary variable for if we can insert or not
	bool b = false;

	//Delimit the list of commas to get the words and push them to the words vector
	while (getline(ss, colval, ',')) {
		if (colval != "") {
			colvals.push_back(colval);
		}
		else {
			colvals.push_back("-1");
		}
	}

	//if colvals more than columns then terminate insert
	if (colvals.size() > columns.size())
	{
		AlertMessage(table, inputLine, "\nprovided # of column values is greater than number of columns of table");
		return;
	}

	while (colvals.size() < columns.size())
	{
		colvals.push_back("");
	}

	int row_id = KeyExists(colvals);

	if (row_id > -1)
	{
		for (int i = 0; i < columns.size(); i++)
		{
			DataColumn d = columns.at(i);
			//Get that data columns type
			string type = d.GetType();

			string item;
			//Get the invidual item in the row
			if (i < colvals.size())
			{
				item = colvals.at(i);
			}
			else
			{
				item = "-1";
			}

			//If this columns type is a string, push it to the rows string vector
			if (type.compare("str") == 0) {
				row.id = row_id;
				row.strs.push_back(item);
				count++;
			}

			//Otherwise, if it is an int, push it to the rows integer vector
			if (type.compare("int") == 0) {
				int itemInt = stoi(item);
				row.id = row_id;
				row.ints.push_back(itemInt);
				count++;
			}
		}

		if (count == columns.size())
		{
			InsertItem(row);
			string filename = "data\\DATA_" + table + ".CSV";
			UpdateCsv(filename, colvals, row_id);
			AlertMessage(table, inputLine, "\nRow Updated successfully\n");
			return;
		}
		else
		{
			AlertMessage(table, inputLine, "\nColumns mismatched\n");
		}
	}
	AlertMessage(table, inputLine, "\nrecord not found\n");
}

void Table::SELECT(string values, string table)
{
	string filtervalue= values.substr(values.find_last_of(",") + 1, values.find_last_of(")") - 1 - values.find_last_of(","));

	vector<int> selectedrows;
	bool match_found = false;
	for (int i = 0;i < rows.size();i++)
	{
		DataRow d = rows.at(i);
		for (int k = 0; k < columns.size(); k++) {
			DataColumn c = columns.at(k);
			if (c.GetType().compare("str") == 0) {
				if (d.strs.at(c.GetIndex()) == filtervalue)
				{
					selectedrows.push_back(i);
				}
			}

			if (c.GetType().compare("int") == 0) {
				string num = to_string(d.ints.at(c.GetIndex()));
				if (num == filtervalue)
				{
					selectedrows.push_back(i);
				}
			}
		}
	}

	if (selectedrows.size() > 0)
	{
		AlertMessage(table, values, "Following rows matched");
		while (!selectedrows.empty())
		{
			match_found = true;
			int row_id = selectedrows.back();
			PrintTableRow(row_id);
			selectedrows.pop_back();
		}
	}
	if (!match_found)
	{
		AlertMessage(table, values, "No match found");
	}
}
