//
// Created by Leonardo Fuso on 09/05/18.
//

#include "compiler.h"
#include "token.h"

struct Token
{
    TokenType tokenType;
    const char *value;
    const char *body;
    const char *source;
};

struct Line
{
    int line_address;
    char *body;
    unsigned numtkns;
    struct Token **tokens;
    int error;
};

struct Line **
lexical_analysis(File *filePtr, int lncnt)
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

    printf("Identified Tokens:\n");

    unsigned int lnum;
    for (lnum = 1; (fgets(raw_line, LINE_SIZE, filePtr) != NULL); ++lnum)
    {
        /*
         *  It does the exchange of '\n' for '\0'
         */
        if (strchr(raw_line, '\n') != NULL)
            *(strchr(raw_line, '\n')) = '\0';

        /*
         *  Produce the Tokens using the line information
         */
        lncomplete = _strbldr(lnum, raw_line);

        if (lncomplete != NULL)
            program[lncnt++] = lncomplete;
        else
        {
            printf("Unexpected behavior: L162 compiler.c - Closing ...");
            exit(1);
        }

        if (lncomplete->error != 0)
            break;
    }
    return program;
}

int
syntax_analysis(struct Line **);

File *
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

int
_line_counter(File *filePtr)
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

int
compile(char *path)
{
    FILE *filePtr;
    unsigned int lncnt = 0;
    struct Line **program = NULL;
    struct Line *lncomplete = NULL;

    char *raw_line = NULL;

    unsigned int lnum;

    filePtr = _file_opener(path);

    if (filePtr != NULL)
        printf("\nName file '%s' opened successfully.\n", path);

    lncnt = _line_counter(filePtr);

}