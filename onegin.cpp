#include "onegin.h"
#include "tech_func_onegin.h"


struct Bufer* InitBuferForFile (char* input_file_name) {
	struct Bufer* bufer = (struct Bufer* ) calloc (1, sizeof (struct Bufer));
	assert (bufer);

	bufer->data = ReadFromFile(bufer, input_file_name); 
	bufer->n_strings = NumberOfStrings (bufer->data);
	bufer->strings = (char**) calloc (bufer->n_strings, sizeof (char*));
	CleaningTheTextStyle (bufer);
	FillStringsInBufer (bufer);
	return bufer;
}

char* ReadFromFile (struct Bufer* bufer, char* input_file_name) {
	assert (bufer);

	FILE* input_file = NULL;
	if ((input_file = fopen (input_file_name, "rb"))) {
		unsigned long long len = LenOfFile (input_file);
		bufer->len = len;
		char* data = (char* ) calloc (len, sizeof (char));
		fread (data, sizeof (char), len, input_file);
		fclose (input_file);
		return data;
	}
	else {
		printf ("Error in InitText!");
		return NULL;
	}
}

unsigned long long LenOfFile (FILE* file) {
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
	while (data[i] != '\0') {
		if (data[i] == '\n')
			number_of_strings++;
		i++;
	}
	return number_of_strings + 1;
}

// Return 1, if char is '/0', '/n', '/r'.
int IsFinalCharacters (char c) {
	if (c == '\n' || c == '\r' || c == '\0')
		return 1;
	return 0;
}

void CleaningTheTextStyle (struct Bufer* bufer) {
	assert (bufer);
	assert (bufer->data);

	unsigned long long low = 0;
	unsigned long long fast = 1;
	unsigned long long i = 1;

	while (bufer->data[fast]) {
		if (IsFinalCharacters (bufer->data[fast]) && !IsFinalCharacters (bufer->data[low]))
			bufer->data[i] = '\0';

		else if (IsFinalCharacters (bufer->data[fast]) && IsFinalCharacters (bufer->data[low])) {
			i--;
			bufer->len--;
		}
		else
			bufer->data[i] = bufer->data[fast];
		low++;
		fast++;
		i++;
	}
}

void FillStringsInBufer (struct Bufer* bufer) {
	assert (bufer);
	assert (bufer->data);
	assert (bufer->strings);

	bufer->strings[0] = bufer->data;
	int string_number = 1;
	unsigned long long low = 0;
	unsigned long long fast = 1;

	while (fast < bufer->len) {
		// printf ("fast = %c, low = %c\n", bufer->data[fast], bufer->data[low]);
		if (!IsFinalCharacters (bufer->data[fast]) && IsFinalCharacters (bufer->data[low])) {
			bufer->strings[string_number] = bufer->data + fast;
			// printf ("Fill struct by string = %s\n", bufer->strings[string_number]);
			string_number++;
		}
		low++;
		fast++;
	}
}

void PrintSortedTextToConsole (struct Bufer* bufer) {
	assert (bufer);

	for (int i = 0; i < bufer->n_strings; i++) {
		printf ("%s\n", bufer->strings[i]);
	}
}


void PrintSortedTextToFile (struct Bufer* bufer, char* output_file_name) {
	assert (bufer);

	FILE* out_file = NULL;
	if ((out_file = fopen (output_file_name, "a"))) {
		fprintf (out_file, "\n---------------------------------\nSorted text:\n"
										"---------------------------------\n");
		for (int i = 0; i < bufer->n_strings; i++) {
			fprintf (out_file, "%s\n", bufer->strings[i]);
			fflush (out_file); 		// Вопрос, какой смысл в этом?
		}
		putc ('\0', out_file);
		fclose (out_file);
	}
	else {
		printf ("Error in Writing");
	}
}


void CleanFile (char* file_name) {
	FILE* out_file = NULL;
	out_file = fopen (file_name, "w");
	fflush (out_file); 					//Зачем?
	fclose (out_file);

}

void PrintRowTextToFile (struct Bufer* bufer, char* output_file_name) {
	assert (bufer);
	assert (bufer->data);

	FILE* out_file = fopen (output_file_name, "a");
	fprintf (out_file, "---------------------------------\nRow Text:\n"
									"---------------------------------\n");
	unsigned long long i = 0;

	while (i < bufer->len) {
		if (bufer->data[i] == '\0' && i != bufer->len - 1)
			putc ('\n', out_file);
		else {
			putc (bufer->data[i], out_file);
		}
		i++;
	}
	fclose (out_file);
}

void PrintRowTextToConsole (struct Bufer* bufer) {
	assert (bufer);
	assert (bufer->data);

	unsigned long long i = 0;

	while (i < bufer->len) {
		if (bufer->data[i] == '\0' && i != bufer->len - 1)
			putchar ('\n');
		else {
			putchar (bufer->data[i]);
		}
		i++;
	}
}


void SortStringsAlphabet (struct Bufer* bufer, enum sorting_mode mode) {
	assert (bufer);

	// printf ("Buufer->n_strings = %d\n", bufer->n_strings);
	for (int k = 0; k < bufer->n_strings - 1; k++) {
		for (int i = k + 1; i < bufer->n_strings; i++) {
			if (CompareStrings (bufer->strings[i], bufer->strings[k]) > 0) {
				if (mode == DESCENDING) {
					// printf ("%s ------ %s SWAP\n", bufer->strings[i], bufer->strings[k]);
					SwapStrings (bufer->strings, i, k);
				}
				// printf ("%s ------ %s        ELSE\n", bufer->strings[i], bufer->strings[k]);
			}
			else if (mode == ASCENDING) {
				// printf ("ERRRRRRORORORORO\n");
				SwapStrings (bufer->strings, i, k);
			}
		}
	}
}

void SwapStrings (char** strings, int a, int b) {
	char* tempData = 0;
	tempData = strings[a];
	strings[a] = strings[b];
	strings[b] = tempData;	
}


int CompareStrings (char* string1, char* string2) {
	int i = 0;
	while (string1[i] != '\0' && string2[i] != '\0' && string1[i] == string2[i]){
		i++;
	}
	return string1[i] - string2[i];
}

void CleanMemoryOfBufer (struct Bufer *bufer) {
	free (bufer->strings);
	free (bufer->data);
	free (bufer);
}