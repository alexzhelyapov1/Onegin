#include "onegin.h"


int main () {
	struct Bufer *bufer = InitBuferForFile("input.txt");

	CleanFile ("output.txt");

	printf ("Row Text:");
	printf ("\n-------------\n");
	PrintRowTextToFile (bufer, "output.txt");
	PrintRowTextToConsole (bufer);
	printf ("\n-------------\n");

	printf ("Sorted Text:");
	printf ("\n-------------\n");
	SortStringsAlphabet (bufer, ASCENDING);
	PrintSortedTextToConsole (bufer);
	PrintSortedTextToFile (bufer, "output.txt");


	// Проверить правильно ли чиститься память
	free (bufer->data);
	free (bufer);
	return 0;
}