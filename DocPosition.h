#pragma once
#include <vector>
#include <string>

using namespace std;

// Позиция в документе
class DocPosition
{
private:
	int num; // Номер по порядку
	string name; // Наименование
	int qty; // Кол-во
	vector<string> catalogs; // Каталоги
public:
	DocPosition(int num, string name, int qty, vector<string> catalogs);
	int getNum();
	string getName();
	int getQty();
	vector<string> getCatalogs();
};