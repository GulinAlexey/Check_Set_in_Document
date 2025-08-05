#pragma once
#include <vector>
#include <string>

using namespace std;

// Позиция в документе
class DocPosition
{
private:
	int num; // Номер по порядку
	int qty; // Кол-во
	vector<string> catalogs; // Каталоги
public:
	DocPosition(int num, int qty, vector<string> catalogs);
	int getNum();
	int getQty();
	vector<string> getCatalogs();
};