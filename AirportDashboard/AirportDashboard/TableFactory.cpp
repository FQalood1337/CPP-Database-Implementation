#include "includes.h"
#include "TableFactory.h"
#include "table.h"


vector<string> TableFactory::FindSchema(string table) {
    for (int i = 0; i < schemaData.size(); i++) {
        string t = schemaData.at(i).at(0);
        if (t.compare(table) == 0) {
            return schemaData.at(i);
        }
    }
    
}


Table TableFactory::CreateTable(string tableName, string file) {
    Table t;
    t.InitializeTableSchema(FindSchema(tableName));
    t.InitializeTableData(GetTableDataFromFile("data/" + file));


    return t;
}


void TableFactory::PrintSchemaData() {
    cout << endl << "-------------------------------------------- " << endl;

    //Double for loop over the vector
    for (int i = 0; i < schemaData.size(); i++) {
        vector<string> vec = schemaData.at(i);
        for (int j = 0; j < vec.size(); j++) {
            //Lets do a little extra formatting to make sure it looks real nice
            string s = vec.at(j);
            if (s.length() < 10) {
                s.append(10 - s.length(), ' ');
            }

            if (s.length() > 9) {
                s = s.substr(0, 10);
            }

            cout << "|" << s << "| \t";
        }
        cout << endl;
    }

    cout << endl << "-------------------------------------------- " << endl;

}

void TableFactory::InitializeSchema() {
    //Load the schema file
    ifstream input_from_file("data/tables_schema.csv");

    //Where we store the line
    string line;

    while (getline(input_from_file, line)) {

        line += ",";

        stringstream ss(line);

        string word;

        vector<string> words;

        //Delimit the list of commas to get the words and push them to the words vector
        while (getline(ss, word, ',')) {
            if (word != "") {
                words.push_back(word);
            }
        }
        //Push the vector of words to the schema data 2D vecttor
        schemaData.push_back(words);

    }
}

vector<vector<string>> TableFactory::GetTableDataFromFile(string file) {
    vector<vector<string>> data;
    
    //Load the input file
    ifstream input_from_file(file);

    //Where we store the line
    string line;

    while (getline(input_from_file, line)) {

        line += ",";

        stringstream ss(line);

        string word;

        vector<string> words;

        //Delimit the list of commas to get the words and push them to the words vector
        while (getline(ss, word, ',')) {
            if (word != "") {
                words.push_back(word);
            }
            else {
                words.push_back("NULL");
            }
        }
        //Push the vector of words to the schema data 2D vecttor
        data.push_back(words);

    }

    return data;

}