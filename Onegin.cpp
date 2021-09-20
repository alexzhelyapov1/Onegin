#include "Onegin.h"


struct Bufer *InitBufer () {
	struct Bufer *bufer = (struct Bufer *) calloc (1, sizeof (struct Bufer));
	assert (bufer);
	bufer->str = InitText(bufer); 
	puts (bufer->str);
	N_Str (bufer);
	bufer->strings = (struct String *) calloc (bufer->n_strings, sizeof (struct String));
	RemoveRN (bufer);
	FillStruct (bufer);
	return bufer;
}


char *InitText (struct Bufer *bufer) {
	assert (bufer);
	FILE *txtFile = NULL;
	if ((txtFile = fopen ("text.txt", "rb")) != NULL) {
		long len = LenOfFile (txtFile);
		bufer->len = len;
		char *str = (char *) calloc (len, sizeof (char));
		fread (str, sizeof (char), len, txtFile);
		fclose (txtFile);
		return str;
	}
	else {
		printf ("Error in InitText!");
		return NULL;
	}
}


long LenOfFile (FILE *file) {
	assert (file != NULL);

	fseek (file, 0, SEEK_END);
	long len = ftell (file) + 1;
	rewind(file);
	return len;
}


void N_Str (struct Bufer *bufer) {
	assert (bufer);
	assert (bufer->str != NULL);

	bufer->n_strings = 0;
	char *i = bufer->str - 1;
	while ((i = strchr (i + 1, '\n')) != NULL) {
		bufer->n_strings++;
	}
	bufer->n_strings++;
}


struct String *FillStruct (struct Bufer *bufer) {
	assert (bufer);
	assert (bufer->str != NULL);
	assert (bufer->strings != NULL);

	bufer->strings->data = bufer->str;
	int stringNumber = 0;
	char *i = bufer->str - 1;
	while (i != bufer->endFile && (i = strchr (i + 1, '\0')) != NULL) {
		bufer->strings[stringNumber].len = i - bufer->strings[stringNumber].data;
		stringNumber++;
		*i = '\0';
		bufer->strings[stringNumber].data = i + 1;
	}
	return bufer->strings; 
}


void RemoveRN (struct Bufer *bufer) {
	assert (bufer);
	char *i = bufer->str;
	bufer->endFile = strchr (i, '\0');
	int carret = 0;
	for (int k = 0; k < bufer->len; k++) {
		if (i[k] == '\n')
			i[carret] = '\0';
		else if (i[k] == '\0')
			break;
		else if (i[k] == '\r')
			carret--;
		else
			i[carret] = i[k];
		carret++;
	}
	i[carret] = '\0';
}


void SortStringsLen (struct Bufer *bufer) {		// пузырьком
	assert (bufer);
	int n_strings = bufer->n_strings;
	for (; n_strings > 1; n_strings--) {
		for (int i = 0; i < n_strings - 1; i++) {
			if (bufer->strings[i].len < bufer->strings[i + 1].len) {
				SwapStringsInStruct (bufer->strings, i);
			}
		}
	}
}


void PrintSortTextConsole (struct Bufer *bufer) {
	assert (bufer);
	printf ("-------------\n");
	for (int i = 0; i < bufer->n_strings; i++) {
		printf ("%s\n", bufer->strings[i].data);
	}
}


void PrintSortTextFile (struct Bufer *bufer) {
	assert (bufer);
	FILE *wFile = NULL;
	if ((wFile = fopen ("result.txt", "wb")) != NULL) {
		for (int i = 0; i < bufer->n_strings; i++) {
			fprintf (wFile, "%s\n", bufer->strings[i].data);
			fflush (stdout);
		}
	}
	else {
		printf ("Error in Writing");
	}
}


void SortStringsAlphabet (struct Bufer *bufer) {
	assert (bufer);
	for (int k = 0; k < bufer->n_strings - 1; k++) {
		for (int i = 0; i < bufer->n_strings - 1; i++) {
			if (CompareStrings (bufer->strings[i].data, bufer->strings[i + 1].data) > 0) {
				SwapStringsInStruct (bufer->strings, i);
			}
		}
	}
}


void SortStringsAlphabetReverse (struct Bufer *bufer) {
	assert (bufer);

	for (int k = 0; k < bufer->n_strings; k++) {
		for (int i = 0; i < bufer->n_strings - 1; i++) {
			if (CompareStringsReverse (bufer->strings[i].data, bufer->strings[i].len, bufer->strings[i + 1].data,
				 bufer->strings[i + 1].len) > 0) {

				SwapStringsInStruct (bufer->strings, i);
			}
		}
	}
}


void SwapStringsInStruct (struct String *strings, int i) {
	int tempLen = 0;
	char *tempData = 0;
	tempLen = strings[i].len;
	tempData = strings[i].data;
	strings[i].len = strings[i + 1].len;
	strings[i].data = strings[i + 1].data;
	strings[i + 1].len = tempLen;
	strings[i + 1].data = tempData;	
}


int CompareStrings (char *string1, char *string2) {
	int i = 0;
	while (string1[i] != '\0' && string2[i] != '\0' && string1[i] == string2[i])
		i++;
	return string1[i] - string2[i];
}


int CompareStringsReverse (char *string1, int len1, char *string2, int len2) {
	int i = 0;
	len1--;
	len2--;
	while (i < len1 && i < len2 && string1[len1 - i] == string2[len2 - i]){
		i++;
	}
	return string1[len1 - i] - string2[len2 - i];
}


void TestPrintDigitStr (struct Bufer *bufer) {
	assert (bufer);
	printf ("PRINTING\n");
	int i = 0;
	char *s = bufer->str;
	char *endFile = bufer->endFile;
	while (&s[i] != endFile) {
		printf("%d ", s[i]);
		i++;
	}
	printf("%d ", s[i]);
	printf ("PRINTING\n");
}
