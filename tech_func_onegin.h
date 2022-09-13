#ifndef TECH_FUNC_ONEGIN_INCLUDED
#define TECH_FUNC_ONEGIN_INCLUDED

char* ReadFromFile (struct Bufer* bufer, char* input_file_name);    // Read test form file to bufer->data
void FillStringsInBufer (struct Bufer* bufer);                      // Fill strings array with ptrs to strings in text
int NumberOfStrings (char* data);                                   // Return number of strings in out text
unsigned long long LenOfFile (FILE* file);
void CleaningTheTextStyle (struct Bufer* bufer);                    // Replace /r, /n -> /0. Clean repeat
int IsFinalCharacters (char c);                                     // Return 1, if char is '/0', '/n', '/r'
void SwapStrings (char** strings, int a, int b);
int CompareStrings (char* string1, char* string2);
int CompareStringsRhyme (char* string1, char* string2);

#endif