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
		int *str = (char *) calloc (len, sizeof (char));
		//int frRes = 
		fread (str, sizeof (int), len, txtFile);
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
	assert (str != NULL);
	assert (strings != NULL);

	strings[0].data = str;

	int stringNumber = 0;
	char *i = str + 1;
	while ((i = strchr (i + 1, '\n')) != NULL) {
		strings[stringNumber].len = i - strings[stringNumber].data;		//случчай когда \n\0 получается строка длины 0
		stringNumber++;
		strings[stringNumber].data = i + 1;
	}

	//printf ("1 - %i, 2 - %i\n", strchr (str, '\0'), strings[stringNumber].data);
	strings[stringNumber].len = strchr (str, '\0') - strings[stringNumber].data;
	*strchr (str, '\0') = '\n'; // теперь у нас все строки без завершающего нуля
	return strings;
}


long lenOfFile (FILE *file) {
	assert (file != NULL);

	fseek (file, 0, SEEK_END);
	long len = ftell (file) + 1;
	rewind(file);
	return len;
}


void TestOutStrings (int n_strings, struct String *strings) {
	assert (strings != NULL);

	for (int i = 0; i < n_strings; i++) {
		printf ("Str #%i, len = %i, firstElement = %c\n", i + 1, strings[i].len, *strings[i].data);
	}
}


void SortStringsLen (struct String *strings, int n_strings) {		// пузырьком
	assert (strings != NULL);

	for (; n_strings > 1; n_strings--) {
		for (int i = 0; i < n_strings - 1; i++) {
			if (strings[i].len < strings[i + 1].len) {
				SwapStrings (strings, i);
			}
		}
	}
}


void PrintSortTextConsole (struct String *strings, int n_strings) {
	assert (strings != NULL);

	for (int i = 0; i < n_strings; i++) {
		char *pos = strings[i].data;
		while (*pos != '\n' && *pos != '\0') {
			putchar (*pos);
			pos++;
		}
		if (i != n_strings - 1) {
			putchar ('\n');
		}
	}
	putchar ('\0');
}


void PrintSortTextFile (struct String *strings, int n_strings) {
	assert (strings != NULL);

	FILE *wFile = NULL;
	if ((wFile = fopen ("result.txt", "wb")) != NULL) {
		for (int i = 0; i < n_strings; i++) {
			char *pos = strings[i].data;
			while (*pos != '\n' && *pos != '\0') {
				putc (*pos, wFile);
				pos++;
			}
			if (i != n_strings - 1) {
				putc ('\n', wFile);
			}
		}
		putc ('\0', wFile);
	}
	else {
		printf ("Error in Writing");
	}
}


void SortStringsAlphabet (struct String *strings, int n_strings) {
	assert (strings != NULL);

	for (; n_strings > 1; n_strings--) {
		for (int i = 0; i < n_strings - 1; i++) {
			CompareStrings (strings, i);
		}
	}
}


void SwapStrings (struct String *strings, int i) {
	int tempLen = 0;
	char *tempData = 0;
	tempLen = strings[i].len;
	tempData = strings[i].data;
	strings[i].len = strings[i + 1].len;
	strings[i].data = strings[i + 1].data;
	strings[i + 1].len = tempLen;
	strings[i + 1].data = tempData;	
}


// 	for (; n_strings > 1; n_strings--) {
// 		for (int i = 0; i < n_strings - 1; i++) {
// 			if (strings[i].len < strings[i + 1].len) {
// 				int tempLen = 0;
// 				char *tempData = 0;
// 				tempLen = strings[i].len;
// 				tempData = strings[i].data;
// 				strings[i].len = strings[i + 1].len;
// 				strings[i].data = strings[i + 1].data;
// 				strings[i + 1].len = tempLen;
// 				strings[i + 1].data = tempData;
// 			}
// 			if (strings[i].len == strings[i+1].len) {
// 				needMoreDeepSort = true;
// 			}
// 		}
// 	}
// }


void CompareStrings (struct String *strings, int first) {
	int i = 0;
	int second = first + 1;
	char *fCh = strings[first].data;
	char *sCh = strings[second].data;

	while (*(fCh + i) == *(sCh + i) && *(fCh + i) != '\n' && *(sCh + i) != '\n') {
		if (*(strings[first].data + i) == '\n') {
			break;
		}
		else {
			i++;
		}

		//(*(strings[first].data + i) == '\n') ? break : i++;
	}
	if (*fCh + i == '\n') { 		//более короткие строки будут падать вниз
		SwapStrings (strings, first);
	}
	else if ((*strings[first].data + i) >= (*strings[second].data + i)) {
		SwapStrings (strings, first);
	}
}