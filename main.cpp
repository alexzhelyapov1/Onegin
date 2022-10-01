#include "onegin.h"


int main () {
	struct Bufer *bufer = InitBuferForFile("hamlet.txt");

	CleanFile ("output.txt");

	// PrintRawTextToFile (bufer, "output.txt");
	SortStringsAlphabet (bufer, 0, bufer->n_strings - 1);
	// SortStringsRhyme (bufer, 0, bufer->n_strings - 1);
	PrintSortedTextToFile (bufer, "output.txt");
	
	CleanMemoryOfBufer (bufer);
	IsPunctuationMark('a');
	return 0;
}