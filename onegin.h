#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <string.h>
#include <assert.h>

// Modes of debugging:
// FULL_LOGGING - logs all events to console
// ERR_LOGGING - printf all errors to console
// RELEASE - do not printf others
#define RELEASE

#ifdef FULL_LOGGING
    #define deb_message(code) code
    #define err_message(code) code
#endif
#ifdef ERR_LOGGING
    #define deb_message(code)  
    #define err_message(code) code
#endif
#ifdef RELEASE
    #define deb_message(code)  
    #define err_message(code)
#endif

struct Bufer {
	int n_strings;				// Number of strings in text
	char* data; 				// Global data from file
	char** strings;		// Array of pointers to strings in data
	unsigned long len;		// Length of data in chars, with closing \0
};

enum sorting_mode {
	ASCENDING,
	DESCENDING
};

// -----------------------------Main functions of library--------------------------------------------------------------
struct Bufer* InitBuferForFile (const char* input_file_name);						// Read text form file to buffer
void PrintSortedTextToFile (struct Bufer* bufer, const char* output_file_name);
void SortStringsAlphabet (struct Bufer* bufer, int first_number, int last_number);			// Sorting text in buffer
void SortStringsRhyme (struct Bufer* bufer, int first_number, int last_number);
void PrintRawTextToFile (struct Bufer* bufer, const char* output_file_name);
void CleanFile (const char* file_name);
void CleanMemoryOfBufer (struct Bufer *bufer);									// Clean ouput file

// -----------------------------Internal functions----------------------------------------------------------------------
void ReadFromFile (struct Bufer* bufer, const char* input_file_name);    	// Read test form file to bufer->data
void FormatText(struct Bufer* bufer);								// Delete extra spaces and /0 strings. Replace /r, /n -> /0.
void FillStringsInBufer(struct Bufer* bufer);                     	// Fill strings array with ptrs to strings in text
void NumberOfStrings(struct Bufer* bufer);                         	// Return number of strings in out text
unsigned long LenOfFile(FILE* file);
int IsFinalCharacters(char c);                                     // Return 1, if char is '/0', '/n', '/r'
void SwapStrings(char** strings, int a, int b);
int CompareStrings(char* string1, char* string2);
int CompareStringsRhyme(char* string1, char* string2);
int IsPunctuationMark (char a);                                     // Is it not letter
int FindPartitionAlphabet(struct Bufer* bufer, int first_number, int last_number);
int FindPartitionRhyme(struct Bufer* bufer, int first_number, int last_number);

#endif