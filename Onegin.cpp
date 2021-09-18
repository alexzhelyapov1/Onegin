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
		long len = LenOfFile (txtFile);
		printf ("Total len = %li\n", len);
		fflush (stdout);
		char *str = (char *) calloc (len, sizeof (char));
		fread (str, sizeof (char), len, txtFile);

		fclose (txtFile);
		return str;
	}
	else {
		printf ("Error in InitText!");
		fflush (stdout);
		return NULL;
	}
}


struct String *FillStruct (char *str, struct String *strings, int n_strings) {
	assert (str != NULL);
	assert (strings != NULL);

	strings[0].data = str;

	int stringNumber = 0;
	char *i = str;
	char *endFile = RemoveN (str);
	while (i != endFile && (i = strchr (i + 1, '\0')) != NULL) {
		strings[stringNumber].len = i - strings[stringNumber].data;		//случчай когда \n\0 получается строка длины 0
		printf ("FillStruct len = %d, endFile = %p, i = %p, endchar = %d, %d\n", strings[stringNumber].len, endFile, i, *(i - 1), '\r');
		fflush (stdout);
		stringNumber++;
		*i = '\0';
		strings[stringNumber].data = i + 1;
	}
	return strings;
}


long LenOfFile (FILE *file) {
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
		fflush (stdout);
	}
}


void SortStringsLen (struct String *strings, int n_strings) {		// пузырьком
	assert (strings != NULL);

	for (; n_strings > 1; n_strings--) {
		for (int i = 0; i < n_strings - 1; i++) {
			if (strings[i].len < strings[i + 1].len) {
				SwapStringsInStruct (strings, i);
			}
		}
	}
}


void PrintSortTextConsole (struct String *strings, int n_strings) {
	assert (strings != NULL);

	for (int i = 0; i < n_strings; i++) {
		printf ("%s\n", strings[i].data);
		fflush (stdout);
	}
}


void PrintSortTextFile (struct String *strings, int n_strings) {
	assert (strings != NULL);

	FILE *wFile = NULL;
	if ((wFile = fopen ("result.txt", "wb")) != NULL) {
		for (int i = 0; i < n_strings; i++) {
			fprintf (wFile, "%s\n", strings[i].data);
			fflush (stdout);
		}
	}
	else {
		printf ("Error in Writing");
		fflush (stdout);
	}
}


void SortStringsAlphabet (struct String *strings, int n_strings) {
	assert (strings != NULL);

	for (; n_strings > 1; n_strings--) {
		for (int i = 0; i < n_strings - 1; i++) {
			if (CompareStrings (strings[i].data, strings[i + 1].data) > 0) {
				SwapStringsInStruct (strings, i);
			}
		}
	}
}


void SortStringsAlphabetReverse (struct String *strings, int n_strings) {
	assert (strings != NULL);

	for (; n_strings > 1; n_strings--) {
		for (int i = 0; i < n_strings - 1; i++) {
			if (CompareStringsReverse (strings[i].data, strings[i].len, strings[i + 1].data, strings[i + 1].len) > 0) {
				SwapStringsInStruct (strings, i);
			}
		}
	}
}


void SwapStringsInStruct (struct String *strings, int i) {
	int tempLen = 0;
	char *tempData = 0;
	tempLen = strings[i].len;
	tempData = strings[i].data;
	strings[i].len = strings[i + 1].len;
	strings[i].data = strings[i + 1].data;
	strings[i + 1].len = tempLen;
	strings[i + 1].data = tempData;	
}


int CompareStrings (char *string1, char *string2) {
	int i = 0;
	while (string1[i] != '\0' && string2[i] != '\0' && string1[i] == string2[i])
		i++;
	return string1[i] - string2[i];
}


int CompareStringsReverse (char *string1, int len1, char *string2, int len2) {
	int i = 0;
	len1--;
	len2--;
	while (i < len1 && i < len2 && string1[len1 - 1 - i] == string2[len2 - 1 - i]){
		printf ("InWhile 1 = %c, 2 = %c, sr1 = %c, sr2 = %c, i = %d, len1 = %d, len2 = %d\n", string1[0], string2[0], string1[len1 - 1 - i], string2[len2 - 1 - i], i, len1, len2);
		fflush (stdout);
		i++;
	}
	printf ("1 = %c, 2 = %c, sr1 = %c, sr2 = %c, i = %d, len1 = %d, len2 = %d\n", string1[0], string2[0], string1[len1 - 1 - i], string2[len2 - 1 - i], i, len1, len2);
	fflush (stdout);
	printf ("---\n");
	fflush (stdout);
	return string1[len1 - 1 - i] - string2[len2 - 1 - i];
}


void TestPrintStr (char *s, char *endFile) {
	int i = 0;
	while (&s[i] != endFile) {
		printf("%d ", s[i]);
		fflush (stdout);
		i++;
	}
	printf("%d ", s[i]);
	fflush (stdout);
}


char *RemoveN (char *str) {
	char *i = str;	
	char *endFile = strchr (str, '\0');							//ПОЧЕМУ ВЫЛЕЗАЕТ ОШИБКА, ЕСЛИ INT ??
	while ((i = strchr (i + 1, '\n')) != NULL) {
		*i = '\0';
	}
	TestPrintStr (str, endFile);
	return endFile;
}


char *RemoveR (char *str) {

	char *str1 = (char *) calloc (strlen)
}