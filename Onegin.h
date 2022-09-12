#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <string.h>
#include <assert.h>


struct String {
	char *data;		//ссылка на 1 элемент строки
	int len;
};

struct Bufer {
	int n_strings;				
	char *data; 				// Global data from file
	char *end_file;				// ???
	struct String *strings;		// Array of pointers to strings in data
	unsigned long long len;		// Length of data in chars, with closing \0
};


struct Bufer *InitBufer ();
char *ReadFromFile (struct Bufer *bufer);
void FillStringsInBufer (struct Bufer *bufer);
int NumberOfStrings (struct Bufer *bufer);
unsigned long long LenOfFile (FILE *file);

void SortStringsLen (struct Bufer *bufer);
void PrintSortTextConsole (struct Bufer *bufer);
void PrintSortTextFile (struct Bufer *bufer);
void SortStringsAlphabet (struct Bufer *bufer);
void SwapStringsInStruct (struct String *strings, int i);
int CompareStrings (char *string1, char *string2);
int CompareStringsReverse (char *string1, int len1, char *string2, int len2);
void SortStringsAlphabetReverse (struct Bufer *bufer);
// void RemoveRNInData (struct Bufer *bufer);					// Remove /r, /n in data for text style
void TestPrintDigitStr (struct Bufer *bufer);
void PrintRowText (struct Bufer *bufer);
void CleanOutFile ();
void PrintRowTextFile (struct Bufer *bufer);

#endif