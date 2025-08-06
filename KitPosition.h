#pragma once
#include <string>

using namespace std;

// Позиция в наборе
class KitPosition
{
private:
	string catalog; // Наименование каталога
	int qty; // Кол-во
public:
	KitPosition(string catalog, int qty);
	string getCatalog();
	int getQty();
};