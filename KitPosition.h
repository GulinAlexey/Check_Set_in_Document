#pragma once
#include <string>

using namespace std;

// Позиция в наборе
class KitPosition
{
private:
	string catalog; // Каталог
	int qty; // Кол-во
public:
	KitPosition(string catalog, int qty);
	string getCatalog();
	int getQty();
};