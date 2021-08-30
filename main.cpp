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
	struct String *strings = (struct String *) calloc (n_strings, sizeof (struct String));
	FillStruct (str, strings, n_strings);
	TestOutStrings (n_strings, strings);


	cleanMemory ();
	return 0;
}