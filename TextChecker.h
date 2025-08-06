#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "DocPosition.h"
#include "KitPosition.h"

#define CELL_SIZE 15 // кол-во символов в одном столбце при выводе позиций документа в консоль

using namespace std;

class TextChecker
{
private:
	vector <DocPosition> docPositions; // Позиции в документе (среди которых нужно найти совпадения с набором)
	vector <KitPosition> kitPositions; // Позиции в наборе
public:
	void getPositionsFromDoc(string filename); // Считать позиции документа из файла
	void getPositionsFromKit(string filename); // Считать позиции набора из файла
	bool checkKitInDoc(); // Проверить наличие набора в документе
	static int countStringsInInputFile(string inputFileName); // Получение кол-ва строк таблицы в файле
	static bool onlyNumInStrCheck(const char* str); // Проверка, что в строке char* только символы чисел (в том числе без "-")
	static void printDocPositions(vector <DocPosition> *positions); // Вывести на экран позиции документа
};