// Count word frequencies ... jas, 2010

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORDS 5000

// Global data structures
char *words[MAXWORDS];
int   freqs[MAXWORDS];
int   nwords = 0;

// Functions on these structures
int getWord(char *);
int findWord(char *);
int addWord(char *);

// Scan file, count word frequencies, display sorted list

int main(int argc, char **argv)
{
	char word[1000];
	int i;

	while (getWord(word)) {
		// printf("%s\n",word); // debugging
		i = findWord(word);
		if (i < 0) {
			i = addWord(word);
		}
		freqs[i]++;
	}
	for (i = 0; i < nwords; i++) {
		printf("%6d   %s\n", freqs[i], words[i]);
	}
	return EXIT_SUCCESS;
}

// getWord: extracts normalised version of word from stdin
// - buf is a string buffer to hold word read from input
// - produces normalised version of the word (lower-cased, '..' trimmed, etc)
// - returns 1 if a word was found, 0 otherwise
// - after trimming, we may have no chars left, hence the do{}while loop

int getWord(char *buf)
{
	int ch, n;
	char *c;
	const char *wordChars = "abcdefghijklmnopqrstuvwxyz'";

	do {
		c = buf;
		while ((ch = getchar()) != EOF) {
			ch = tolower(ch);
			if (strchr(wordChars,ch)) break;
		}
		if (ch == EOF) return 0;
		*c++ = ch;
		while ((ch = getchar()) != EOF) {
			ch = tolower(ch);
			if (!strchr(wordChars,ch)) break;
			*c++ = ch;
		}
		*c = '\0';
		if (c == buf) return 0;
		// remove "'" at the start of word
		if (buf[0] == '\'') {
			for (c = buf+1; *c != '\0'; c++)
				*(c-1) = *c;
			*(c-1) = '\0';
		}
		// remove "'" at end of word
		n = strlen(buf)-1;
		if (buf[n] == '\'') {
			buf[n] = '\0';
		}
		// remove "'s" at end of word
		n = strlen(buf)-1;
		if (buf[n-1] == '\'' && buf[n] == 's') {
			buf[n-1] = '\0';
		}
		// after removing stuff above,
		// the word may be empty, so try again
	} while (strlen(buf) == 0);
	return 1;
}

// findWord: search for word in dictionary
// returns index or -1 if not found

int findWord(char *w)
{
	int i;  int foundPos = -1;

	for (i = 0; i < nwords; i++) {
		if (strcmp(w, words[i]) == 0) {
			foundPos = i;
		}
	}
	return foundPos;
}


// addWord: add a new word into dictionary
// returns index of where it was added

int addWord(char *w)
{
	words[nwords] = w;
	freqs[nwords] = 0;
	return nwords++;
}
