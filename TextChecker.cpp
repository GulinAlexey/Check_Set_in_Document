#include "TextChecker.h"

void TextChecker::getPositionsFromDoc(string filename) // Считать позиции документа из файла
{
	int n = countStringsInInputFile(filename); // получение кол-ва строк таблицы в файле
	if (n == 0)
	{
		cout << "Во входном файле \"" << filename << "\" отсутствуют данные." << endl;
		exit(1);
	}
	ifstream finp; // указатель на файл для чтения
	finp.open(filename); // открыть файл для чтения
	string fstr; // строка для чтения из файла
	for (int i = 0; i < n; i++) // чтение строк из файла
	{
		string substr; // подстрока для чтения из строки
		bool skipLine = false; // флаг для пропуска строки
		getline(finp, fstr, '\n'); // получить строку из файла
		istringstream istr(fstr); // создать поток из строки для получения подстрок в строке

		// Заполняемые поля для новой позиции
		int num = -1;
		string name = "";
		int qty = -1;
		vector<string> catalogs;

		for (int j = 0; !istr.eof(); j++) // пока не будет пройдена вся строка
		{
			string newCatalog;

			istr >> substr; // прочитать подстроку из строки
			if (substr != "" && substr != " ") // если подстрока прочитана корректно
			{
				switch (j)
				{
				case 0: // Номер по порядку
					// если первым элементом строки является не число (порядковый номер), то пропустить её
					// (например, это шапка таблицы)
					if (!onlyNumInStrCheck(substr.c_str()))
					{
						skipLine = true;
						break;
					}
					num = atoi(substr.c_str());
					break;
				case 1: // Наименование
					name = substr;
					break;
				case 2: // Кол-во
					// Если это не число, то это часть наименования (например, "сок" в наименовании "яблочный сок")
					if (!onlyNumInStrCheck(substr.c_str()))
					{
						name = name + " " + substr;
						j--;
						break;
					}
					qty = atoi(substr.c_str());
					break;
				default: // Один из каталогов
					// Пропустить побочные слова в строке
					if(substr == "шт" || substr == "шт.")
						break;
					newCatalog = substr;
					// Удалить первый символ из строки, если это "("
					if (newCatalog.front() == '(') 
						newCatalog.erase(0, 1);
					// Удалить последний символ из строки, если это "," или ")"
					if (newCatalog.back() == ',' || newCatalog.back() == ')')
						newCatalog.pop_back();
					catalogs.push_back(newCatalog);
				}
				if (skipLine)
					break;
			}
		}
		if (!skipLine)
			this->docPositions.push_back(DocPosition(num, name, qty, catalogs));
	}
}

void TextChecker::getPositionsFromKit(string filename) // Считать позиции набора из файла
{
	int n = countStringsInInputFile(filename); //получение кол-ва строк таблицы в файле
	if (n == 0)
	{
		cout << "Во входном файле \"" << filename << "\" отсутствуют данные." << endl;
		exit(1);
	}
	ifstream finp; // указатель на файл для чтения
	finp.open(filename); // открыть файл для чтения
	string fstr; // строка для чтения из файла
	for (int i = 0; i < n; i++) // чтение строк из файла
	{
		string substr; // подстрока для чтения из строки
		bool skipLine = false; // флаг для пропуска строки
		getline(finp, fstr, '\n'); // получить строку из файла
		istringstream istr(fstr); // создать поток из строки для получения подстрок в строке

		// Заполняемые поля для новой позиции
		string catalog = "";
		int qty = -1;

		for (int j = 0; !istr.eof(); j++) // пока не будет пройдена вся строка
		{
			string newCatalog;

			istr >> substr; // прочитать подстроку из строки
			if (substr != "" && substr != " ") // если подстрока прочитана корректно
			{
				if (j == 0) // Наименование каталога
				{
					// пропустить строку, являющуюся шапкой таблицы
					if (substr == "Каталог" || substr == "каталог")
					{
						skipLine = true;
						break;
					}
					catalog = substr;
				}
				else // Кол-во
				{
					// Пропустить побочные слова в строке
					if (substr != "-" && substr != "--" && substr != "---")
					{
						qty = atoi(substr.c_str());
						break;
					}
				}
			}
		}
		if (!skipLine)
			this->kitPositions.push_back(KitPosition(catalog, qty));
	}
}

bool TextChecker::checkKitInDoc() // Проверить наличие набора в документе
{
	bool isKitInDoc = true;
	vector <DocPosition> docPositionsWithKit; // Результирующий список позиций в документе, соответствующий набору
	// Искать соответствия для каждой позиции в наборе
	for (int i = 0; i < this->kitPositions.size(); i++)
	{
		string catalogName = this->kitPositions[i].getCatalog();
		int catalogQty = this->kitPositions[i].getQty(); // Оставшееся кол-во для данного каталога, которое нужно найти в документе
		bool isCatalogInDoc = false;
		// Искать соответствия для набора в каждой позиции документа
		for (int j = 0; j < this->docPositions.size(); j++)
		{
			vector<string> catalogsInDocPosition = this->docPositions[j].getCatalogs();
			// Искать соответствия для набора в списке каталогов позиции документа
			for (int k = 0; k < catalogsInDocPosition.size(); k++) 
			{
				if (catalogsInDocPosition[k] == catalogName) 
				{
					// Уменьшить оставшееся кол-во, которое нужно найти
					catalogQty -= this->docPositions[j].getQty();
					isCatalogInDoc = true;
					docPositionsWithKit.push_back(this->docPositions[j]);
					break;
				}
			}
			if (catalogQty <= 0) // Уже найдено достаточно позиций документа для позиции набора
				break;
		}
		// Если каталог не найден или количество недостаточное
		if (!isCatalogInDoc || catalogQty > 0)
		{
			isKitInDoc = false;
			break;
		}
	}
	if (!isKitInDoc)
		cout << "Набор не содержится в документе." << endl;
	else
	{
		cout << "Набор содержится в документе." << endl;
		cout << "Состав набора:" << endl;
		printDocPositions(&docPositionsWithKit);
	}
	return isKitInDoc;
}

int TextChecker::countStringsInInputFile(string inputFileName) // Получение кол-ва строк таблицы в файле
{
	ifstream finp; //указатель на файл с входными данными
	string word; //строка для чтения из файла
	finp.open(inputFileName); //открыть файл для чтения
	int n = 0;
	if (finp.is_open()) //если файл удалось открыть
	{
		while (!finp.eof()) //пока не прочитает весь файл
		{
			getline(finp, word, '\n'); //получить отдельное значение из файла
			if (word != "") //если прочитанное значение не пустое
				n += 1; //увеличить кол-во значений на 1
		}
		finp.close(); //закрыть файл
	}
	return n;
}

bool TextChecker::onlyNumInStrCheck(const char* str) // Проверка, что в строке char* только символы чисел (в том числе без "-")
{
	if (str == NULL || *str == '\0') // проверка на пустую строку
		return false;
	for (int i = 0; str[i] != '\0'; i++) // проверка, что в строке только числа
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

void TextChecker::printDocPositions(vector <DocPosition> *positions) // Вывести на экран позиции документа
{
	cout << left << setw(CELL_SIZE) << "Позиция" << setw(CELL_SIZE*2) << "Наименование" << setw(CELL_SIZE) << "Кол-во" << "Каталоги" << endl;
	for (int i=0; i<positions->size(); i++)
	{
		cout << left << setw(CELL_SIZE) << (*positions)[i].getNum();
		cout << left << setw(CELL_SIZE*2) << (*positions)[i].getName();
		cout << left << (*positions)[i].getQty() << setw(CELL_SIZE-1) << " шт.";
		vector<string> catalogs = (*positions)[i].getCatalogs();
		cout << "(";
		for (int j = 0; j < catalogs.size(); j++)
		{
			cout << catalogs[j];
			if (j != catalogs.size() - 1)
				cout << ", ";
		}
		cout << ")" << endl;
	}
}