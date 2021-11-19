
#include <iostream>
#include "includes.h"
#include "TableFactory.h"
using namespace std;
int main()
{
    //Initialize the table factory
    TableFactory factory;
    Table initTable; 

    //Initialize the table schema within the factory
    factory.InitializeSchema();
    factory.PrintSchemaData();

    //File Data going to be streamed into 2D array 
    vector<vector<string>> fData; 

    //Prompt user for the input file they wish to load
	cout << "Welcome to the Airport Dashboard!" << endl;
	cout << "Please Input The File You Wish To Load(fileName.extension):\n";
	fstream fin;
	ofstream fout;
	string fileName;
	cin >> fileName;

    //Attempt tp open the file
    fin.open(fileName, ios::in);

    //If file fails to load, prompt again until proper file given
    if (fin.fail())
    {
        while (fin.fail())    
        {
            std::cout << "Error in opening fin." << std::endl;
            std::cout << "Try again.\n";

            std::cin >> fileName;
            fin.open(fileName);
        }
    }

    //A string representing a line of input, used for parsing over the input file
    string inputLine;
    string tableCSV;

    //Loop over the initial schema to load it
    do {
        
        //Strings for the CSV and table name
        string tableName;
        //Get the current line
        getline(fin, inputLine);

        //If this is the empty space between the first set of lines and the queries, ignore it and break the loop.
        if (inputLine == "") {
            break;
        }

        //Grab the table csv file from the line
        tableCSV = inputLine.substr(0, inputLine.find("\t"));
        //Grab the tableName file 
        tableName = inputLine.substr(inputLine.find_last_of("\t") + 1, inputLine.length() - inputLine.find_last_of("\t"));

        //Print it out as a debug thing for now
        cout << "'" << tableCSV << "'\t\t\t'" << tableName << "'" << endl;

        

    } while (inputLine != "");

    ifstream fileStream; 

    fileStream.open(tableCSV, ios::in); 
    
    string line;

    while (getline(fileStream, line)) 
    {

        line += ",";

        stringstream ss(line);

        string bits;

        vector<string> data;

        //Delimit the list of commas to get the data and push them to the data vector
        while (getline(ss, bits, ',')) {

            data.push_back(bits);
        }
        //Push the vector of data to the schema data 2D vecttor
        fData.push_back(data);

    }

    fileStream.close(); 

    initTable(fData); 

}

