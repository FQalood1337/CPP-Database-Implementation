
#include <iostream>
#include "includes.h"
#include "TableFactory.h"
using namespace std;

int find_table(vector<Table> tables, string table)
{
    for (int i = 0; i < tables.size(); i++)
    {
        if (table == tables.at(i).GetTitle())
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    //Initialize the table factory
    TableFactory factory;

    //Initialize the table schema within the factory
    factory.InitializeSchema();
    factory.PrintSchemaData();

    //Create a vector of tables that we can access later down the road
    vector<Table> tables;

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

        tables.push_back(factory.CreateTable(tableName, tableCSV));
        

    } while (inputLine != "");

    getline(fin, inputLine);
    cout << inputLine;

    for (int i = 0; i < tables.size(); i++)
    {
        tables.at(i).PrintTable();
    }



    //Loop over the commands and execute each command using its corresponding function
    do {
        getline(fin, inputLine);
        string tableName;
        string values;
        if (inputLine != "")
        {
            cout << "\n---------------------------------------------\n";
            //extracting command from input line read from the input file
            string command = inputLine.substr(0, inputLine.find("("));

            //extracting table name from input line read from the input file
            tableName = inputLine.substr(inputLine.find_last_of(",")+1, inputLine.length()- inputLine.find_last_of(",")-2);
                       
            if (command == "INSERT")
            {
                //check table exists or not
                int tableidx = find_table(tables, tableName);
                
                if (tableidx != -1)
                {
                    Table temp = tables.at(tableidx);
                    DataRow row;

                    //get table title
                    cout << "\n"<< temp.GetTitle()<<"\n";

                    //execute INSERT command
                    tables.at(tableidx).INSERT(inputLine, tableName);
                }
                else
                {
                    cout << "Table: " << tableName << endl;
                    cout << inputLine;
                    cout << "\ntable not found in Database!\n";
                }
                command = "";
                cout << "\n---------------------------------------------\n";

            }
            if (command == "UPDATE")
            {
                //check table exists or not
                int tableidx = find_table(tables, tableName);

                if (tableidx != -1)
                {
                    Table temp = tables.at(tableidx);
                    DataRow row;

                    //get table title
                    cout << "\n" << temp.GetTitle() << "\n";

                    //execute UPDATE command
                    tables.at(tableidx).UPDATE(inputLine, tableName);
                }
                else
                {
                    cout << "Table: " << tableName << endl;
                    cout << inputLine;
                    cout << "\ntable not found in Database!\n";
                }
                command = "";
                cout << "\n---------------------------------------------\n";

            }
            if (command == "SELECT")
            {
                //check table exists or not
                tableName = inputLine.substr(inputLine.find(")") + 2, inputLine.find_last_of(",")-3-inputLine.find(")"));
                
                int tableidx = find_table(tables, tableName);
                if (tableidx != -1)
                {
                    Table temp = tables.at(tableidx);
                    DataRow row;

                    //get table title
                    cout << "\n" << temp.GetTitle() << "\n";
                    tables.at(tableidx).SELECT(inputLine, tableName);
                }
                else
                {
                    cout << "Table: " << tableName << endl;
                    cout << inputLine;
                    cout<< "\ntable not found in Database!\n";
                }

                command = "";
                cout << "\n---------------------------------------------\n";

            }
        }
    } while (inputLine != "WRITE()");//these commands are to be implement in the final submission sprint.

    
    fin.close();
}

