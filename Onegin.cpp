#include "Onegin.h"

int N_Str (char *s) { // strchr
	assert (s != NULL);

	if (s == NULL) {
		return NULL;
	}
	int n_str = 0;
	char *i_s = s - 1;
	while ((i_s = strchr (i_s + 1, '\n')) != NULL) {
		n_str++;
	}
	n_str++;
	return n_str;
}


char *InitText () {
	FILE *txtFile = NULL;
	if ((txtFile = fopen ("text.txt", "rb")) != NULL) {
		long len = lenOfFile (txtFile);
		printf ("Total len = %li\n", len);
		char *str = (char *) calloc (len, sizeof (char));
		int frRes = fread (str, sizeof (char), len, txtFile);
		//printf ("frRes = %i\n", frRes);
		//printf ("String = %d\n", *str);		//если использовать функции, то str можно вывести только puts (str)?
		fclose (txtFile);

		return str;
	}
	else {
		printf ("Error in InitText!");
		return NULL;
	}
}

struct String *FillStruct (char *str, struct String *strings, int n_strings) {
	strings[0].data = str;

	int stringNumber = 0;
	char *i = str + 1;
	while ((i = strchr (i + 1, '\n')) != NULL) {
		strings[stringNumber].len = i - strings[stringNumber].data;		//случчай когда \n\0 получается строка длины 0
		stringNumber++;
		strings[stringNumber].data = i + 1;
	}

	printf ("1 - %i, 2 - %i\n", strchr (str, '\0'), strings[stringNumber].data);
	strings[stringNumber].len = strchr (str, '\0') - strings[stringNumber].data;
	return strings;
}


long lenOfFile (FILE *file) {
	fseek (file, 0, SEEK_END);
	long len = ftell (file) + 1;
	rewind(file);
	return len;
}


void TestOutStrings (int n_strings, struct String *strings) {
	for (int i = 0; i < n_strings; i++) {
		printf ("Str #%i, len = %i, firstElement = %c\n", i + 1, strings[i].len, *strings[i].data);
	}
}

