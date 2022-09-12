#include "Onegin.h"


struct Bufer *InitBufer () {
	struct Bufer *bufer = (struct Bufer *) calloc (1, sizeof (struct Bufer));
	assert (bufer);

	bufer->data = ReadFromFile(bufer); 
	bufer->n_strings = NumberOfStrings (bufer->data);
	bufer->strings = (struct String *) calloc (bufer->n_strings, sizeof (struct String));
	// RemoveRNInData (bufer);
	FillStringsInBufer (bufer);
	return bufer;
}


char *ReadFromFile (struct Bufer *bufer) {
	assert (bufer);

	FILE *txtFile = NULL;
	if (txtFile = fopen ("text.txt", "rb")) {
		unsigned long long len = LenOfFile (txtFile);
		bufer->len = len;
		char *str = (char *) calloc (len, sizeof (char));
		fread (str, sizeof (char), len, txtFile);
		fclose (txtFile);
		return str;
	}
	else {
		printf ("Error in InitText!");
		return NULL;
	}
}


unsigned long long LenOfFile (FILE *file) {
	assert (file != NULL);

	fseek (file, 0, SEEK_END);
	unsigned long long len = ftell (file) + 1; //including in len the closing \0
	rewind(file);
	return len;
}


int NumberOfStrings (char* data) {
	assert (data);

	int number_of_strings = 0;
	unsigned long long i = 0;
	while (data[i] != '/0') {
		if (data[i] == '/n')
			number_of_strings++;
		i++;
	}
	return number_of_strings + 1;
}


void FillStringsInBufer (struct Bufer *bufer) {
	assert (bufer);
	assert (bufer->data);
	assert (bufer->strings);

	bufer->strings[0].data = bufer->data;
	int string_number = 1;
	unsigned long long low = 0;
	unsigned long long fast = 1;

	while (bufer->data[fast]) {
		if ((bufer->data[low] == '\r' || bufer->data[low] == '\n') && bufer->data[fast] != '\r'
																   && bufer->data[fast] != '\n') {
			bufer->strings[string_number].data = bufer->data + fast;
			string_number++;
		}
		low++;
		fast++;
	}
}

// Debugged it to here ---------------------------------------------------


void SortStringsLen (struct Bufer *bufer) {		// пузырьком
	assert (bufer);
	int n_strings = bufer->n_strings;
	for (; n_strings > 1; n_strings--) {
		for (int i = 0; i < n_strings - 1; i++) {
			if (bufer->strings[i].len < bufer->strings[i + 1].len) {
				SwapStringsInStruct (bufer->strings, i);
			}
		}
	}
}


void PrintSortTextConsole (struct Bufer *bufer) {
	assert (bufer);
	for (int i = 0; i < bufer->n_strings; i++) {
		printf ("%s\n", bufer->strings[i].data);
	}
}


void PrintSortTextFile (struct Bufer *bufer) {
	assert (bufer);
	FILE *wFile = NULL;
	if ((wFile = fopen ("result.txt", "ab")) != NULL) {
		fprintf (wFile, "\nSorted text:\n\n");
		for (int i = 0; i < bufer->n_strings; i++) {
			fprintf (wFile, "%s\n", bufer->strings[i].data);
			fflush (stdout);
		}
		fclose (wFile);
	}
	else {
		printf ("Error in Writing");
	}
}


void CleanOutFile () {
	FILE *wFile = NULL;
	wFile = fopen ("result.txt", "wb");
	fflush (stdout);
	fclose (wFile);

}

void PrintRowTextFile (struct Bufer *bufer) {
	assert (bufer);
	char *i = bufer->str;
	FILE *wFile = fopen ("result.txt", "ab");
	fprintf (wFile, "Row Text:\n\n");
	while (i != bufer->end_file) {
		if (*i == '\0') 
			putc ('\n', wFile);
		else
			putc (*i, wFile);
		i++;
	}
	putc ('\0', wFile);
	putc ('\n', wFile);
	fclose (wFile);
}


void PrintRowText (struct Bufer *bufer) {
	assert (bufer);
	char *i = bufer->str;
	while (i != bufer->end_file) {
		if (*i == '\0') 
			putchar ('\n');
		else
			putchar (*i);
		i++;
	}
	putchar ('\0');
}


void SortStringsAlphabet (struct Bufer *bufer) {
	assert (bufer);
	for (int k = 0; k < bufer->n_strings - 1; k++) {
		for (int i = 0; i < bufer->n_strings - 1; i++) {
			if (CompareStrings (bufer->strings[i].data, bufer->strings[i + 1].data) > 0) {
				SwapStringsInStruct (bufer->strings, i);
			}
		}
	}
}


void SortStringsAlphabetReverse (struct Bufer *bufer) {
	assert (bufer);

	for (int k = 0; k < bufer->n_strings; k++) {
		for (int i = 0; i < bufer->n_strings - 1; i++) {
			if (CompareStringsReverse (bufer->strings[i].data, bufer->strings[i].len, bufer->strings[i + 1].data,
				 bufer->strings[i + 1].len) > 0) {

				SwapStringsInStruct (bufer->strings, i);
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
	while (i < len1 && i < len2 && string1[len1 - i] == string2[len2 - i]){
		i++;
	}
	return string1[len1 - i] - string2[len2 - i];
}


void TestPrintDigitStr (struct Bufer *bufer) {
	assert (bufer);
	printf ("PRINTING\n");
	int i = 0;
	char *s = bufer->str;
	char *end_file = bufer->end_file;
	while (&s[i] != end_file) {
		printf("%d ", s[i]);
		i++;
	}
	printf("%d ", s[i]);
	printf ("PRINTING\n");
}
