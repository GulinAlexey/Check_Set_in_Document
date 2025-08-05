#include "TextChecker.h"

void TextChecker::getPositionsFromDoc(string filename)
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
		int num = 0;
		string name = "";
		int qty = 0;
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
						skipLine = true;
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
			docPositions.push_back(DocPosition(num, name, qty, catalogs));
	}
}

void TextChecker::getPositionsFromKit(string filename)
{
	int n = countStringsInInputFile(filename); //получение кол-ва строк таблицы в файле
	if (n == 0)
	{
		cout << "Во входном файле \"" << filename << "\" отсутствуют данные." << endl;
		exit(1);
	}
	// TODO
}

void TextChecker::checkKitInDoc()
{

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