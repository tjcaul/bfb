#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> //For srand()

/* configuration */
#define PAT_VALID "#" //Characters to replace in pattern file
#define RANDOM_FILL true
/* end configuration */

#define BF_VALID "+-<>[].,"

void usage (char **argv)
{
	printf("usage: %s pattern [bf]\n", argv[0]);
	exit(1);
}

char seekchar (FILE *file, const char *search,
		const char *warn, bool echo)
{
	char c;
	while ((c = getc(file)) != EOF) {
		if (strchr(search, c))
			return c;
		if (echo)
			putchar(c);
		if (warn && strchr(warn, c)) //Program won't work with a stray bf character
			fprintf(stderr, "Warning: character %c in input\n", c);
	}
	return EOF;
}

void dump (FILE *file, const char *valid)
{
	char c;
	while ((c = getc(file)) != EOF)
		if (strchr(valid, c))
			putchar(c);
}

int main (int argc, char **argv)
{
	char *bfname = NULL;
	char *patname = NULL;
	char pc;
	FILE *patfile, *bffile = stdin;
	bool bfeof = false; //Optimization to prevent repeatedly polling an empty stream

	if (argc == 3) {
		patname = argv[1];
		bfname = argv[2];
	} else if (argc == 2) {
		patname = argv[1];
	} else {
		usage(argv);
	}

	if (bfname)
		bffile = fopen(bfname, "r");
	if (patname)
		patfile = fopen(patname, "r");

	srand(time(NULL));

	while ((pc = seekchar(patfile, PAT_VALID, BF_VALID, true)) != EOF) {
		char c;
		if (!bfeof) {
			c = seekchar(bffile, BF_VALID, NULL, false);
			if (c == EOF)
				bfeof = true;
		}
		if (bfeof) {
			if (RANDOM_FILL)
				c = (rand()%2) ? '+' : '-'; //No effect after program has finished (hopefully)
			else
				c = pc;
		}
			
		putchar(c);
	}

	if (!bfeof) { //Dump extra bf
		//...but not if nothing will be dumped
		char c = seekchar(bffile, BF_VALID, NULL, false);
		if (c != EOF) {
			putchar('\n');
			putchar(c);
			dump(bffile, BF_VALID);
			putchar('\n');
		}
	}

	return 0;
}
