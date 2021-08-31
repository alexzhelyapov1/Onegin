#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <string.h>
#include <assert.h>


int main () {
	char s[] = {"0asdk qw"};
	printf ("%s", s);
	printf ("%i", s[0]);

	// char *str = (char *) calloc (len, sizeof (char)); // нужно на \0 доп байт?
	// fopen (str, sizeof (char), len, txtFile);
	// char *genLine = (char *) calloc (strlen (txtFile), sizeof (char));
}