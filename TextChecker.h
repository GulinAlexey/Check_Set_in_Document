#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "DocPosition.h"
#include "KitPosition.h"

using namespace std;

class TextChecker
{
private:
	vector <DocPosition> docPositions; // Позиции в документе (среди которых нужно найти совпадения с набором)
	vector <KitPosition> kitPositions; // Позиции в наборе
public:
	void getPositionsFromDoc(string filename);
	void getPositionsFromKit(string filename);
	void checkKitInDoc();
	int countStringsInInputFile(string inputFileName); // Получение кол-ва строк таблицы в файле
	bool onlyNumInStrCheck(const char* str); // Проверка, что в строке char* только символы чисел (в том числе без "-")
};