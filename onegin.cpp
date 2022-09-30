#include "onegin.h"
#include "tech_func_onegin.h"


struct Bufer* InitBuferForFile (char* input_file_name) {
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
	struct Bufer* bufer = (struct Bufer* ) calloc (1, sizeof (struct Bufer));
	deb_message(printf("Allocation for buffer result = %d.\n", bufer);)
	assert (bufer);

	bufer->data = ReadFromFile(bufer, input_file_name);
	bufer->n_strings = NumberOfStrings (bufer->data);
	// CleaningTheTextStyle (bufer);
	FormatText (bufer);
	bufer->strings = (char**) calloc (bufer->n_strings, sizeof (char*));
	FillStringsInBufer (bufer);
	return bufer;
}

char* ReadFromFile (struct Bufer* bufer, char* input_file_name) {
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
	assert (bufer);

	FILE* input_file = NULL;
	if ((input_file = fopen (input_file_name, "rb"))) {
		unsigned long long len = LenOfFile (input_file);
		bufer->len = len;
		char* data = (char* ) calloc (len, sizeof(char));
		deb_message(printf("Allocated %d bytes for data\n", len * sizeof(char));)
		fread (data, sizeof (char), len, input_file);
		fclose (input_file);
		deb_message(printf("%s", data);)
		return data;
	}
	else {
		err_message(printf ("Error in InitText!\n");)
		return NULL;
	}
}

void FormatText (struct Bufer* bufer) {				// Removing extra spacing
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
	assert (bufer);
	assert (bufer->data);

	unsigned long long low = 1;
	unsigned long long fast = 0;
	unsigned long long i = 1;

	char* data = bufer->data;
	while (fast + 1 < bufer->len) {
		if ((IsFinalCharacters(data[fast]) || (fast == 0) && (data[fast + 1] == ' ' || IsFinalCharacters(data[fast + 1])))	{		// When strings starts with tabs or it's zero string
			while (fast + 1 < bufer->len && (data[fast + 1] == ' ' || IsFinalCharacters(data[fast + 1]))) fast++;
		}
		while (data[fast] == ' ' && data[fast + 1] == ' ') fast++;									// More than 1 space
		// while (IsFinalCharacters(data[fast]) && IsFinalCharacters(data[fast + 1])) fast++;
		if (!IsFinalCharacters(data[fast + 1]))
			data[low] = data[fast + 1];
		else
			data[low] = '\0';
		low++;
		fast++;
	}
	bufer->len = low;
	deb_message(printf("New len of data = %d\n", bufer->len);)
}

unsigned long long LenOfFile (FILE* file) {
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
	assert (file != NULL);

	fseek (file, 0, SEEK_END);
	unsigned long long len = ftell (file) + 1; //including in len the closing \0
	rewind(file);
	return len;
}

int NumberOfStrings (char* data) {
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
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
	// deb_message(printf("IsFinalCharacters");)
	if (c == '\n' || c == '\r' || c == '\0')
		return 1;
	return 0;
}

void CleaningTheTextStyle (struct Bufer* bufer) {
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
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
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
	assert (bufer);
	assert (bufer->data);
	assert (bufer->strings);

	bufer->strings[0] = bufer->data;
	int string_number = 1;
	unsigned long long low = 0;
	unsigned long long fast = 1;

	while (fast < bufer->len) {
		if (!IsFinalCharacters (bufer->data[fast]) && IsFinalCharacters (bufer->data[low])) {
			bufer->strings[string_number] = bufer->data + fast;
			string_number++;
		}
		low++;
		fast++;
	}
}

void PrintSortedTextToConsole (struct Bufer* bufer) {
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
	assert (bufer);

	printf ("\n---------------------------------\nSorted text:\n"
										"---------------------------------\n");

	for (int i = 0; i < bufer->n_strings; i++) {
		printf ("%s\n", bufer->strings[i]);
	}
}

void PrintSortedTextToFile (struct Bufer* bufer, char* output_file_name) {
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
	assert (bufer);

	FILE* out_file = NULL;
	if ((out_file = fopen (output_file_name, "a"))) {
		fprintf (out_file, "\n---------------------------------\nSorted text:\n"
										"---------------------------------\n");
		for (int i = 0; i < bufer->n_strings; i++) {
			fprintf (out_file, "%s\n", bufer->strings[i]);
		}
		putc ('\0', out_file);
		fclose (out_file);
	}
	else {
		printf ("Error in Writing\n");
	}
}

void PrintRowTextToFile (struct Bufer* bufer, char* output_file_name) {
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
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
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
	assert (bufer);
	assert (bufer->data);

	printf ("---------------------------------\nRow Text:\n"
									"---------------------------------\n");

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

void SortStringsAlphabet (struct Bufer* bufer, enum sorting_mode mode, int first_number, int last_number) {
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
	assert (bufer);

	if (first_number >= last_number) return;
	int left = first_number;
	int right = last_number;
	int pivot = (first_number + last_number) / 2;	// Nearly middle element

	while (left >= 0 && right > 0 && right < bufer->n_strings && left < right && left <= pivot) {
		if (CompareStrings (bufer->strings[left], bufer->strings[right]) > 0) {
			if (mode == ASCENDING) {
				SwapStrings (bufer->strings, left, right);
			}
		}
		else if (mode == DESCENDING) {
				SwapStrings (bufer->strings, left, right);
		}
		left++;
		right--;
	}
	if (first_number != right) {
		SortStringsAlphabet (bufer, mode, first_number, left);
		SortStringsAlphabet (bufer, mode, left, last_number);
	}
}

void SortStringsRhyme (struct Bufer* bufer, enum sorting_mode mode, int first_number, int last_number) {
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
	assert (bufer);

	if (first_number >= last_number) return;
	int left = first_number;
	int right = last_number;
	int pivot = (first_number + last_number) / 2;	// Nearly middle element

	while (left >= 0 && right > 0 && right < bufer->n_strings && left < right && left <= pivot) {
		if (CompareStringsRhyme (bufer->strings[left], bufer->strings[right]) > 0) {
			if (mode == ASCENDING) {
				SwapStrings (bufer->strings, left, right);
			}
		}
		else if (mode == DESCENDING) {
				SwapStrings (bufer->strings, left, right);
		}
		left++;
		right--;
	}
	if (first_number != right) {
		SortStringsRhyme (bufer, mode, first_number, left);
		SortStringsRhyme (bufer, mode, left, last_number);
	}
}

void SwapStrings (char** strings, int a, int b) {
	deb_message(printf("SwapStrings id1 = %d, id2 = %d\n", a, b);)
	char* tempData = 0;
	tempData = strings[a];
	strings[a] = strings[b];
	strings[b] = tempData;	
}

int CompareStrings (char* string1, char* string2) {
	if (!string1 || !string2) return -1;
	int i = 0;
	while (string1[i] != '\0' && string2[i] != '\0' && string1[i] == string2[i]){
		i++;
	}
	return string1[i] - string2[i];
}

int CompareStringsRhyme (char* string1, char* string2) {
	int i = strlen (string1) - 1;
	int j = strlen (string2) - 1;
	while (i > 0 && j > 0 && string1[i] == string2[i]){
		i--;
		j--;
	}
	return string1[i] - string2[j];
}

void CleanFile (char* file_name) {
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
	FILE* out_file = NULL;
	out_file = fopen (file_name, "w");
	fclose (out_file);

}

void CleanMemoryOfBufer (struct Bufer *bufer) {
	deb_message(printf(__FUNCTION__, "\n"); printf("\n");)
	free (bufer->strings);
	free (bufer->data);
	free (bufer);
}