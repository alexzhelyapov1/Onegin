#include "onegin.h"


int main () {
	struct Bufer *bufer = InitBuferForFile("input.txt");

	CleanFile ("output.txt");

	PrintRowTextToFile (bufer, "output.txt");
	PrintRowTextToConsole (bufer);

	SortStringsRhyme (bufer, ASCENDING);
	PrintSortedTextToConsole (bufer);
	PrintSortedTextToFile (bufer, "output.txt");
	
	CleanMemoryOfBufer (bufer);
	return 0;
}