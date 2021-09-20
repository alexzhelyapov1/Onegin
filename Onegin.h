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
	char *str;
	int n_strings;
	char *endFile;
	struct String *strings;
	long len;
};


struct Bufer *InitBufer ();
char *InitText (struct Bufer *bufer);
struct String *FillStruct (struct Bufer *bufer);
void N_Str (struct Bufer *bufer);
long LenOfFile (FILE *file);

void TestOutStrings (struct Bufer *bufer);
void SortStringsLen (struct Bufer *bufer);
void PrintSortTextConsole (struct Bufer *bufer);
void PrintSortTextFile (struct Bufer *bufer);
void SortStringsAlphabet (struct Bufer *bufer);
void SwapStringsInStruct (struct String *strings, int i);
int CompareStrings (char *string1, char *string2);
int CompareStringsReverse (char *string1, int len1, char *string2, int len2);
void SortStringsAlphabetReverse (struct Bufer *bufer);
void TestPrintStr (char *s, char *endFile);
void RemoveN (struct Bufer *bufer);
void RemoveRN (struct Bufer *bufer);


#endif