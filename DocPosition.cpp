#include "DocPosition.h"

DocPosition::DocPosition(int num, string name, int qty, vector<string> catalogs)
{
	this->num = num;
	this->name = name;
	this->qty = qty;
	this->catalogs = catalogs;
}

int DocPosition::getNum()
{
	return this->num;
}

string DocPosition::getName()
{
	return this->name;
}

int DocPosition::getQty()
{
	return this->qty;
}

vector<string> DocPosition::getCatalogs()
{
	return this->catalogs;
}
