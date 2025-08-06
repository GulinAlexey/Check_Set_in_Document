// Check_Set_in_Document.cpp: определяет точку входа для приложения.
//

#include "Check_Set_in_Document.h"

#define DOC_FILENAME "document.txt"
#define KIT_FILENAME "kit.txt"

using namespace std;

int main()
{
	setlocale(LC_ALL, "en_US.UTF-8"); // для корректного отображения русских букв
	TextChecker* checker = new TextChecker();
	checker->getPositionsFromDoc(DOC_FILENAME);
	checker->getPositionsFromKit(KIT_FILENAME);
	checker->checkKitInDoc();
	delete checker;
	return 0;
}
