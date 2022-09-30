#include "onegin.h"
#include "tech_func_onegin.h"


struct Bufer* InitBuferForFile (char* input_file_name) {
	deb_message(printf("Func = %s\n", __FUNCTION__);)
	struct Bufer* bufer = (struct Bufer* ) calloc (1, sizeof (struct Bufer));
	deb_message(printf("Allocation for buffer result = %lu.\n", sizeof(*bufer));)
	assert(bufer);

	ReadFromFile(bufer, input_file_name);
	FormatText (bufer);
	deb_message(PrintRowTextToConsole(bufer));
	NumberOfStrings (bufer);
	// CleaningTheTextStyle (bufer);
	bufer->strings = (char**) calloc (bufer->n_strings, sizeof (char*));
	FillStringsInBufer (bufer);
	return bufer;
}

void ReadFromFile (struct Bufer* bufer, char* input_file_name) {
	deb_message(printf("Func = %s\n", __FUNCTION__);)
	assert (bufer);

	FILE* input_file = NULL;
	if ((input_file = fopen (input_file_name, "rb"))) {
		unsigned long long len = LenOfFile (input_file);
		bufer->len = len;

		char* data = (char* ) calloc (len, sizeof(char));
		deb_message(printf("Allocated %lld bytes for data\n", len * sizeof(char));)

		fread (data, sizeof (char), len, input_file);
		deb_message(printf("Len of input = %lld, len of data = %ld\n", len, strlen(data));)
		fclose (input_file);
		deb_message(printf("Readed data:\n---------------------------------\n%s\n---------------------------------\n", data);)
		bufer->data = data;
	}
	else {
		err_message(printf ("Error in InitText!\n");)
	}
}

void FormatText (struct Bufer* bufer) {				// Removing extra spacing
	deb_message(printf("Func = %s\n", __FUNCTION__);)
	assert (bufer);
	assert (bufer->data);
	char* data = bufer->data;

	unsigned long long low = 0;
	unsigned long long fast = 0;
	unsigned long long end = bufer->len - 1;

	while ((fast < bufer->len) && (IsFinalCharacters(data[fast]) || data[fast] == ' '))	fast++;		// Removing starting extra elements
	while ((end >= 0) && (IsFinalCharacters(data[end]) || data[end] == ' '))	end--;		// Removing ending extra elements (need to put \0 in the end)

	printf ("Fast = %d, end = %d\n", fast, end);
	if (fast > end) {
		data[0] = '\0';
		return;
	}

	while (fast + 1 <= end) {
		bool flag_new_str = false;
		bool flag_extra_symbols = false;
		while ((IsFinalCharacters(data[fast]) || data[fast] == ' ') && (IsFinalCharacters(data[fast + 1]) || data[fast + 1] == ' ')) {
			flag_extra_symbols = true;
			if (IsFinalCharacters(data[fast]) || IsFinalCharacters(data[fast + 1])) {
				flag_new_str = true;
			}
			fast++;
			if (fast > end) break;
		}
		if (flag_extra_symbols && flag_new_str) {
			data[low] = '\0';
		}
		else if (flag_extra_symbols) {
			data[low] = ' ';
		}
		else {
			data[low] = data[fast];
		}
		low++;
		fast++;
	}
	data[low] = data[end];
	low++;
	data[low] = '\0';
	bufer->len = low + 1;
	deb_message(printf("New len of data = %lld\n", bufer->len);)
}

unsigned long long LenOfFile (FILE* file) {
	deb_message(printf("Func = %s\n", __FUNCTION__);)
	assert (file != NULL);

	fseek (file, 0, SEEK_END);
	unsigned long long len = ftell (file) + 1; //including in len the closing \0
	rewind(file);

	return len;
}

void NumberOfStrings (struct Bufer* bufer) {
	deb_message(printf("Func = %s\n", __FUNCTION__);)
	assert (bufer);
	assert(bufer->data);

	int number_of_strings = 0;
	unsigned long long i = 0;
	while (i < bufer->len) {
		if (IsFinalCharacters(bufer->data[i]))
			number_of_strings++;
		i++;
	}
	bufer->n_strings = number_of_strings;
	deb_message(printf("Number of strings in text = %d\n", bufer->n_strings));
}

// Return 1, if char is '/0', '/n', '/r'.
int IsFinalCharacters (char c) {
	// deb_message(printf("IsFinalCharacters");)
	if (c == '\n' || c == '\r' || c == '\0')
		return 1;
	return 0;
}

void FillStringsInBufer (struct Bufer* bufer) {
	deb_message(printf("Func = %s\n", __FUNCTION__);)
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
	deb_message(printf("Func = %s\n", __FUNCTION__);)
	assert (bufer);

	printf ("\n---------------------------------\nSorted text:\n"
										"---------------------------------\n");

	for (int i = 0; i < bufer->n_strings; i++) {
		printf ("%s\n", bufer->strings[i]);
	}
	printf("\n");
}

void PrintSortedTextToFile (struct Bufer* bufer, char* output_file_name) {
	deb_message(printf("Func = %s\n", __FUNCTION__);)
	assert (bufer);

	FILE* out_file = NULL;
	if ((out_file = fopen (output_file_name, "a"))) {
		fprintf (out_file, "\n---------------------------------\nSorted text:\n"
										"---------------------------------\n");
		for (int i = 0; i < bufer->n_strings; i++) {
			fprintf (out_file, "%s\n", bufer->strings[i]);
		}
		fclose (out_file);
	}
	else {
		printf ("Error in Writing\n");
	}
}

void PrintRowTextToFile (struct Bufer* bufer, char* output_file_name) {
	deb_message(printf("Func = %s\n", __FUNCTION__);)
	assert (bufer);
	assert (bufer->data);

	FILE* out_file = fopen (output_file_name, "a");
	fprintf (out_file, "---------------------------------\nRow Text:\n"
									"---------------------------------\n");
	unsigned long long i = 0;

	while (i < bufer->len - 1) {
		if (bufer->data[i] == '\0' && i != bufer->len - 1)
			putc ('\n', out_file);
		else {
			putc (bufer->data[i], out_file);
		}
		i++;
	}
	printf("\n");
	fclose (out_file);
}

void PrintRowTextToConsole (struct Bufer* bufer) {
	deb_message(printf("Func = %s\n", __FUNCTION__);)
	assert (bufer);
	assert (bufer->data);

	printf ("\n---------------------------------\nRow Text:\n"
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
	printf("\n\n");
}

void SortStringsAlphabet (struct Bufer* bufer, enum sorting_mode mode, int first_number, int last_number) {
	// deb_message(printf("Func = %s\n", __FUNCTION__);)
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
	// deb_message(printf("Func = %s\n", __FUNCTION__);)
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
	while (IsPunctuationMark(string1[i])) i--;
	while (IsPunctuationMark(string2[j])) j--;
	while (i > 0 && j > 0 && string1[i] == string2[i]){
		i--;
		j--;
	}
	return string1[i] - string2[j];
}

int IsPunctuationMark (char a) {
	if (a < 'A' || a > 'z') {
		return 1;
	}
	return 0;
}

void CleanFile (char* file_name) {
	deb_message(printf("Func = %s\n", __FUNCTION__);)
	FILE* out_file = NULL;
	out_file = fopen (file_name, "w");
	fclose (out_file);

}

void CleanMemoryOfBufer (struct Bufer *bufer) {
	deb_message(printf("Func = %s\n", __FUNCTION__);)
	free (bufer->strings);
	free (bufer->data);
	free (bufer);
}