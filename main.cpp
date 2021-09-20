#include "Onegin.h"


int main () { // assert
	// считываем файл в одну переменную
	// проходимся по \n сохраняя указатели и размеры строки в структуру 
	// сортируем структуру
	// выводим в конечный файл по структуре по ссылкам
	struct Bufer *bufer = InitBufer();
	TestOutStrings (bufer);
	//SortStringsLen (strings, n_strings);
	//SortStringsAlphabet (strings, n_strings);
	SortStringsAlphabetReverse (bufer);

	PrintSortTextConsole (bufer);
	PrintSortTextFile (bufer);
	

	free (bufer->str);
	free (bufer->strings);
	free (bufer);
	return 0;
}