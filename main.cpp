#include "Onegin.h"


int main () { // assert
	// считываем файл в одну переменную
	// проходимся по \n сохраняя указатели и размеры строки в структуру 
	// сортируем структуру
	// выводим в конечный файл по структуре по ссылкам

	char *str = InitText(); 
	puts (str);
	int n_strings = N_Str (str);
	printf ("n_strings = %i\n", n_strings);
	printf ("---\n%d buk = %c\n---\n", '\n', 119);
	//TestPrintStr (str);
	printf("Flag1 %d\n", '\r');
	struct String *strings = (struct String *) calloc (n_strings, sizeof (struct String));
	printf ("Flag2\n");
	FillStruct (str, strings, n_strings);
	printf ("Flag3\n");
	TestOutStrings (n_strings, strings);
	//SortStringsLen (strings, n_strings);
	//SortStringsAlphabet (strings, n_strings);
	SortStringsAlphabetReverse (strings, n_strings);

	PrintSortTextConsole (strings, n_strings);
	PrintSortTextFile (strings, n_strings);
	

	free (str);
	free (strings);
	return 0;
}