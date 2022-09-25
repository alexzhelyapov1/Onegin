#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <string.h>
#include <assert.h>

struct Bufer {
	int n_strings;				// Number of strings in text
	char* data; 				// Global data from file
	char** strings;		// Array of pointers to strings in data
	unsigned long long len;		// Length of data in chars, with closing \0
};

enum sorting_mode {
	ASCENDING,
	DESCENDING
};


struct Bufer* InitBuferForFile (char* input_file_name);						// Read text form file to buffer
void PrintSortedTextToConsole (struct Bufer* bufer);
void PrintSortedTextToFile (struct Bufer* bufer, char* output_file_name);
void SortStringsAlphabet (struct Bufer* bufer, enum sorting_mode mode, int first_number, int last_number);			// Sorting text in buffer
void SortStringsRhyme (struct Bufer* bufer, enum sorting_mode mode, int first_number, int last_number);			// Sorting strings from the end
void PrintRowTextToConsole (struct Bufer* bufer);
void PrintRowTextToFile (struct Bufer* bufer, char* output_file_name);
void CleanFile (char* filename);
void CleanMemoryOfBufer (struct Bufer *bufer);									// Clean ouput file

#endif