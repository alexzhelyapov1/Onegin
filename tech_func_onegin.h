#ifndef TECH_FUNC_ONEGIN_INCLUDED
#define TECH_FUNC_ONEGIN_INCLUDED

// Modes of debugging:
// FULL_LOGGING - logs all events to console
// ERR_LOGGING - printf all errors to console
// RELEASE - do not printf others

#define FULL_LOGGING

// if (DEV_MODE == FULL_LOGGING) {
#ifdef FULL_LOGGING
    #define deb_message(code) code
    #define err_message(code) code
#else
    #ifdef ERR_LOGGING
        #define deb_message(code)  
    #endif
#endif

void ReadFromFile(struct Bufer* bufer, char* input_file_name);    // Read test form file to bufer->data
void FormatText(struct Bufer* bufer);								// Delete extra spaces and /0 strings. Replace /r, /n -> /0.
void FillStringsInBufer(struct Bufer* bufer);                      // Fill strings array with ptrs to strings in text
void NumberOfStrings(struct Bufer* bufer);                                   // Return number of strings in out text
unsigned long long LenOfFile(FILE* file);
int IsFinalCharacters(char c);                                     // Return 1, if char is '/0', '/n', '/r'
void SwapStrings(char** strings, int a, int b);
int CompareStrings(char* string1, char* string2);
int CompareStringsRhyme(char* string1, char* string2);
int IsPunctuationMark (char a);                                     // Is it not letter

#endif