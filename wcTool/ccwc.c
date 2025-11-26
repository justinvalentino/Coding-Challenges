#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void count (FILE *fp, int *lines, int *words, int *bytes, int *chars) {
	int c;
	int in_word = 0;

	while ((c = fgetc(fp)) != EOF) {
		(*bytes)++;
		(*chars)++;

		if (c == '\n')
			(*lines)++;

		if (isspace((unsigned char)c)) {
			in_word = 0;
		}
		else if (!in_word) {
			in_word = 1;
			(*words)++;
		}
	}
}

int main (int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage:\n");
		fprintf(stderr," %s filename\n", argv[0]);
		fprintf(stderr, " %s -[cwlm] filename\n", argv[0]);
		return 1;
	}

	char *flag = NULL;
	char *filename;

	if (argc == 2) {
		filename = argv[1];
	}
	else {
		flag = argv[1];
		filename = argv[2];
	}

	FILE *fp = fopen(filename, "r");
	if (!fp) {
		perror("Error opening file");
		return 1;
	}

	int lines = 0,
	    words = 0,
	    bytes = 0,
	    chars = 0;

	count(fp, &lines, &words, &bytes, &chars);
	
	if (flag == NULL) {
		printf("%d %d %d %d %s\n", bytes, lines, words, chars, filename);
	}
	else if (strcmp(flag, "-c") == 0) {
		printf("%d %s\n", bytes, filename);
	}
	else if (strcmp(flag, "-l") == 0) {
		printf("%d %s\n", lines, filename);
	}
	else if (strcmp(flag, "-w") == 0) {
		printf("%d %s\n", words, filename);
	}
	// this would depend on your locale
	else if (strcmp(flag, "-m") == 0) {
		printf("%d %s\n", chars, filename);
	}
	else {
		fprintf(stderr, "Uknown Flag: %s\n", flag);
		return 1;
	}
	return 0;
}
