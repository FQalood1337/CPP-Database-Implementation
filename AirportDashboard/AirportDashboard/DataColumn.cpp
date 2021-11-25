#include "DataColumn.h"
#include "table.h"



DataColumn::DataColumn(string type, string title, int index) {
	this->type = type;
	this->title = title;
	this->index = index;
}

void DataColumn::SetIndex(int index)
{
	this->index = index;
}

int DataColumn::GetIndex()
{
	return this->index;
}


void DataColumn::SetTitle(string title)
{
	this->title = title; 
}

string DataColumn::GetTitle()
{
	return this->title;
}

void DataColumn::SetType(string type)
{
	this->type = type; 
}

string DataColumn::GetType()
{
	return this->type; 
}

