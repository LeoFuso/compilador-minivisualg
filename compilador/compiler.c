//
// Created by Leonardo Fuso on 09/05/18.
//

#include "compiler.h"

struct Line **
lexical_analysis(FILE *, int);

int
syntax_analysis(struct Line **, unsigned int);

FILE *
_file_opener(char *);

void
_token_printer(struct Line **, int, char *);

unsigned int
_line_counter(FILE *);

int
compile(char *path)
{
    FILE *filePtr;
    unsigned int lncnt = 0;
    struct Line **program = NULL;

    filePtr = _file_opener(path);

    if (filePtr == NULL)
    {
        printf("Unexpected behavior: compiler.c 33 - Closing ...");
        exit(1);
    }
    else
        printf("\nName file '%s' opened successfully.\n", path);

    lncnt = _line_counter(filePtr);
    program = lexical_analysis(filePtr, lncnt);

    if (program == NULL)
    {
        printf("Unexpected behavior: compiler.c 42 - Closing ...");
        exit(1);
    }
    else
        printf("\nWriting to file...\n");

    _token_printer(program, lncnt, path);

    printf("\nSuccess. \nThe tokens were created in the file '%s'\nfrom this same directory.\n", path);
    fclose(filePtr);

    printf("\nParsing tokens...\n");
    if (syntax_analysis(program, lncnt))
    {
        printf("\nSuccess. \nThis is a valid program.\n");
    }
}

void
_stck(struct Token * token)
{

}

int
syntax_analysis(struct Line **program, unsigned int lncnt)
{
    int i;
    int j;
    for(i = 0; i < lncnt; ++i)
        for(j = 0; j < program[i]->numtkns; ++j)
            _stck(program[i]->tokens[j]);


    return 1;
}

struct Line **
lexical_analysis(FILE *filePtr, int lncnt)
{
    char *raw_line = NULL;
    struct Line **program = NULL;
    struct Line *lncomplete = NULL;

    /*
     *  Allocates the memory space required for a source line
     */
    raw_line = (char *) malloc(LINE_SIZE * sizeof(char) + 1);

    /*
     *  Allocates the memory space required for the entire program
     */
    program = (struct Line **) malloc(lncnt * (sizeof(struct Line *)));
    lncnt = 0;

    printf("\nIdentified Tokens:\n\n");

    unsigned int lnum;
    for (lnum = 1; (fgets(raw_line, LINE_SIZE, filePtr) != NULL); ++lnum)
    {
        /*
         *  It does the exchange of '\n' for '\0'
         */
        if (strchr(raw_line, '\n') != NULL)
            *(strchr(raw_line, '\n')) = '\0';

        /*
         *  Produces the Tokens using the line information
         */
        lncomplete = _strbldr(lnum, raw_line);

        if (lncomplete != NULL)
            program[lncnt++] = lncomplete;
        else
        {
            printf("Unexpected behavior: compiler.c 97 - Closing ...");
            exit(1);
        }

        if (lncomplete->error != 0)
            break;
    }
    return program;
}

FILE *
_file_opener(char *path)
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
_line_counter(FILE *filePtr)
{
    unsigned int lncnt = 0;
    char *raw_line = NULL;

    /*
     *  Allocates the memory space required for a source line
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
