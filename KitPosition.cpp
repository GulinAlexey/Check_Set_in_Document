#include "KitPosition.h"

KitPosition::KitPosition(string catalog, int qty)
{
	this->catalog = catalog;
	this->qty = qty;
}

string KitPosition::getCatalog()
{
	return this->catalog;
}

int KitPosition::getQty()
{
	return this->qty;
}
