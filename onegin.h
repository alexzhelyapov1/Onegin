#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <string.h>
#include <assert.h>


struct String {
	char* data;		//ссылка на 1 элемент строки
	int len;
};

struct Bufer {
	int n_strings;				
	char* data; 				// Global data from file
	char* end_file;				// ???
	struct String* strings;		// Array of pointers to strings in data
	unsigned long long len;		// Length of data in chars, with closing \0
};

enum sorting_mode {
	ASCENDING,
	DESCENDING
};


struct Bufer* InitBuferForFile (char* input_file_name);
char* ReadFromFile (struct Bufer* bufer, char* input_file_name);
void FillStringsInBufer (struct Bufer* bufer);
int NumberOfStrings (char* data);
unsigned long long LenOfFile (FILE* file);

void CleaningTheTextStyle (struct Bufer* bufer);
int IsFinalCharacters (char c);

void PrintSortedTextToConsole (struct Bufer* bufer);
void PrintSortedTextToFile (struct Bufer* bufer, char* output_file_name);
void SortStringsAlphabet (struct Bufer* bufer, enum sorting_mode);
void SwapStringsInStruct (struct String* strings, int a, int b);
int CompareStrings (char* string1, char* string2);
void PrintRowTextToConsole (struct Bufer* bufer);
void CleanFile (char* filename);
void PrintRowTextToFile (struct Bufer* bufer, char* output_file_name);

#endif