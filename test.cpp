#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <string.h>
#include <assert.h>


int main () {
	FILE *txtFile = fopen ("text.txt", "rb"); //fstat fseek

	fseek (txtFile, 0, SEEK_END);
	int len = ftell (txtFile);
	printf ("%d", len);

	// char *str = (char *) calloc (len, sizeof (char)); // нужно на \0 доп байт?
	// fopen (str, sizeof (char), len, txtFile);
	// char *genLine = (char *) calloc (strlen (txtFile), sizeof (char));


	fclose (txtFile);
}