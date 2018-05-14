//
// Created by Leonardo Fuso on 09/05/18.
//

#include "compiler.h"

FILE *
_openfl(char *);

void
_token_printer(struct Line **, int, char *);

unsigned int
_count_ln(FILE *);

int
compile(char *path)
{
	FILE *filePtr;
	unsigned int lncnt = 0;
	int syntax_result;
	struct Line **program = NULL;

	filePtr = _openfl(path);

	if (filePtr == NULL)
	{
		printf("Unexpected behavior: compiler.c 24 - Closing ...");
		exit(1);
	}
	else
		printf("\nName file '%s' opened successfully.\n", path);

	lncnt = _count_ln(filePtr);
	program = lexical_analysis(filePtr, lncnt);

	if (program == NULL)
	{
		printf("Unexpected behavior: compiler.c 35 - Closing ...");
		exit(1);
	}
	else
		printf("\nWriting to file...\n");

	_token_printer(program, lncnt, path);

	printf("\nSuccess. \nThe tokens were created in the file '%s'\nfrom this same directory.\n", path);
	fclose(filePtr);

	printf("\nParsing tokens...\n");

	syntax_result = syntax_analysis(program, lncnt);
	if (syntax_result)
	{
		printf("\nSuccess. \nThis is a valid program.\n");
	}
	else
	{
		printf("\nError. \nThis is not a valid program.\n");
	}

}

FILE *
_openfl(char *path)
{
	FILE *filePtr;

	if ((filePtr = fopen(path, "r")) == NULL && (filePtr = fopen(strcat(path, ".visualg"), "r")) == NULL)
	{
		printf("File not found.\n");
		exit(0);
	}

	/*
	 *  Checks if the file is empty
	 */
	fseek(filePtr, 0, SEEK_END);

	if (ftell(filePtr) == 0)
	{
		printf("File is empty.\n");
		exit(0);
	}

	rewind(filePtr);
	return filePtr;
}

void
_token_printer(struct Line **program, int lncnt, char *path)
{
	FILE *fileOut;

	fileOut = fopen(strcat(path, ".token"), "w");

	/*
	 * Checks if output file was created
	 */
	if (fileOut == NULL)
	{
		printf("Error opening token file!\n");
		exit(1);
	}

	int i;
	int j;
	for (i = 0; i < lncnt; i++)
	{
		for (j = 0; j < program[i]->numtkns; j++)
			fprintf(fileOut, "%s", program[i]->tokens[j]->body);
		fprintf(fileOut, "\n");
	}

	fclose(fileOut);
}

unsigned int
_count_ln(FILE *filePtr)
{
	unsigned int lncnt = 0;
	char *raw_line = NULL;

	/*
	 *  Allocates the memory space required for a to_parse line
	 */
	raw_line = (char *) malloc(LINE_SIZE * sizeof(char) + 1);

	/*
	 *  Count how many lines the file has
	 */
	while (fgets(raw_line, LINE_SIZE, filePtr) != NULL)
		lncnt++;

	/*
	 *  Rewind file
	 */
	rewind(filePtr);

	free(raw_line);
	return lncnt;
}
