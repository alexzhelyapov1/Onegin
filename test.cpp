#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <string.h>
#include <assert.h>


int main () {
	char s[];
	char a = '1';
	if ((a = getchar ()) == 'q')
		printf ("%s", s);

	// char *str = (char *) calloc (len, sizeof (char)); // нужно на \0 доп байт?
	// fopen (str, sizeof (char), len, txtFile);
	// char *genLine = (char *) calloc (strlen (txtFile), sizeof (char));
}