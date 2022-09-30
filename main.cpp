#include "onegin.h"


int main () {
	struct Bufer *bufer = InitBuferForFile("hamlet.txt");

	CleanFile ("output.txt");

	// PrintRowTextToFile (bufer, "output.txt");
	// PrintRowTextToConsole (bufer);
	SortStringsAlphabet (bufer, ASCENDING, 0, bufer->n_strings - 1);
	// SortStringsRhyme (bufer, ASCENDING, 0, bufer->n_strings - 1);
	// PrintSortedTextToConsole (bufer);
	PrintSortedTextToFile (bufer, "output.txt");
	
	CleanMemoryOfBufer (bufer);
	return 0;
}