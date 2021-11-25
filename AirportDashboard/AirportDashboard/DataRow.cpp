#include "includes.h"
#include "DataRow.h"
#include "TableFactory.h"

DataRow::DataRow()
{
	id = -1;
}



DataRow::DataRow(const DataRow& src) {
	this->ints = src.ints;
	this->strs = src.strs;
	this->id = src.id;
}