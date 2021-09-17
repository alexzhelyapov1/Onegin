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


char *InitText ();
struct String *FillStruct (char *str, struct String *strings, int n_strings);
int N_Str (char *s);
long LenOfFile (FILE *file);
struct String *FillStruct (char *str, struct String *strings);
void TestOutStrings (int n_strings, struct String *strings);
void SortStringsLen (struct String *strings, int n_strings);
void PrintSortTextConsole (struct String *strings, int n_strings);
void PrintSortTextFile (struct String *strings, int n_strings);
void SortStringsAlphabet (struct String *strings, int n_strings);
void SwapStringsInStruct (struct String *strings, int i);
int CompareStrings (char *string1, char *string2);


#endif