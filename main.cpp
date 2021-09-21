#include "Onegin.h"


int main () {
	struct Bufer *bufer = InitBufer();

	CleanOutFile ();
	printf ("Row Text:");
	printf ("\n-------------\n");
	PrintRowTextFile (bufer);
	PrintRowText (bufer);
	printf ("\n-------------\n");
	printf ("Reverse Text:");
	printf ("\n-------------\n");
	SortStringsAlphabetReverse (bufer);

	PrintSortTextConsole (bufer);
	PrintSortTextFile (bufer);
	
	free (bufer->str);
	free (bufer->strings);
	free (bufer);
	return 0;
}