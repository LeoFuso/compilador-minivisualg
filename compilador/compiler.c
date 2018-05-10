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

int
_fndn_listType(char **type_list, int list_size, char *chr_grammar)
{
    int i;
    for (i = 0; i < list_size; i++)
    {
        char *toCompare = type_list[i];
        if (strcmp(toCompare, chr_grammar) == 0)
            return i;
    }
    return -1;
}

void
_stck(struct Token *token)
{
    FILE *fileGrammar;
    char *raw_line = NULL;

    char **type_list = NULL;
    int **grammar_list = NULL;

    raw_line = (char *) malloc(LINE_SIZE * sizeof(char));

    if ((fileGrammar = fopen("../grammar", "r")) == NULL)
    {
        printf("File not found.\n");
        exit(0);
    }

    FILE *fileTypeList;

    if ((fileTypeList = fopen("../typeList", "r")) == NULL)
    {
        printf("File not found.\n");
        exit(0);
    }
    unsigned int lnum;
    int list_size;
    for (lnum = 0; (fgets(raw_line, LINE_SIZE, fileTypeList) != NULL); ++lnum)
    {
        if (lnum == 0)
        {
            list_size = (int) strtol(raw_line, (char **) NULL, 10);
            type_list = (char **) malloc(list_size * sizeof(char *) + 1);
            type_list[0] = raw_line;
        }
        else
        {
            type_list[lnum] = raw_line;
        }

        printf("\n%s", type_list[lnum]);
    }

    char *dlim_spc = " ";
    char *chr_grammar;
    unsigned int snum;
    for (lnum = 0; (fgets(raw_line, LINE_SIZE, fileGrammar) != NULL); ++lnum)
    {
        snum = 0;
        if (lnum == 0)
        {
            int ln_size = (int) strtol(raw_line, (char **) NULL, 10);
            grammar_list = (int **) malloc(ln_size * sizeof(int *));
            grammar_list[0][snum] = ln_size;
        }
        else
        {
            for (chr_grammar = strtok(raw_line, dlim_spc); chr_grammar != NULL; chr_grammar = strtok(NULL, dlim_spc))
            {
                if (snum == 0)
                {
                    int cl_size = (int) strtol(chr_grammar, (char **) NULL, 10);
                    grammar_list[lnum] = (int *) malloc(cl_size * sizeof(int));
                    grammar_list[lnum][snum] = cl_size;
                }
                else if (snum == 1)
                {
                    int val = (int) strtol(chr_grammar, (char **) NULL, 10);
                    grammar_list[lnum][snum] = val;
                }
                else
                {
                    int found = _fndn_listType(type_list, list_size, chr_grammar);
                    if (found == -1)
                        exit(1);

                    grammar_list[lnum][snum] = found;
                }
                snum++;
            }

            /*
             *  It does the exchange of '\n' for '\0'
             */
            if (strchr(raw_line, '\n') != NULL)
                *(strchr(raw_line, '\n')) = '\0';

            type_list[lnum] = raw_line;
            printf("\n%s", type_list[lnum]);

        }

    }


    /* struct Grammar ** nonTerminals = NULL;
     nonTerminals =  (struct Grammar**) malloc(2 * sizeof(struct Grammar*));
     struct Grammar * nonTerminal1 = NULL;
     struct Grammar * nonTerminal2 = NULL;
     struct Grammar * nonTerminal3 = NULL;

     nonTerminals[0] = (struct Grammar*)malloc(sizeof(struct Grammar));

     nonTerminal1 = nonTerminals[0];

     nonTerminal1->is_terminal = 0;
     nonTerminal1->num = 1;
     nonTerminal1->value = (char *)malloc(LINE_SIZE * sizeof(char));
     nonTerminal1->value = "UNIDECLAR";
     nonTerminal1->num_rules = 4;
     nonTerminal1->rules = (struct Grammar**)malloc(4 * sizeof(struct Grammar*));

     nonTerminal1->rules[0] = (struct Grammar*)malloc(sizeof(struct Grammar));
     nonTerminal1->rules[0]->is_terminal = 1;
     nonTerminal1->rules[0]->num = 1;
     nonTerminal1->rules[0]->value = (char *)malloc(LINE_SIZE * sizeof(char));
     nonTerminal1->rules[0]->value = "<var>";
     nonTerminal1->rules[0]->num_rules = 0;
     nonTerminal1->rules[0]->rules = NULL;

     nonTerminal1->rules[1] = (struct Grammar*)malloc(sizeof(struct Grammar));
     nonTerminal1->rules[1]->is_terminal = 1;
     nonTerminal1->rules[1]->num = 2;
     nonTerminal1->rules[1]->value = (char *)malloc(LINE_SIZE * sizeof(char));
     nonTerminal1->rules[1]->value = "<id>";
     nonTerminal1->rules[1]->num_rules = 0;
     nonTerminal1->rules[1]->rules = NULL;

     nonTerminal1->rules[2] = (struct Grammar*)malloc(sizeof(struct Grammar));
     nonTerminal1->rules[2]->is_terminal = 1;
     nonTerminal1->rules[2]->num = 3;
     nonTerminal1->rules[2]->value = (char *)malloc(LINE_SIZE * sizeof(char));
     nonTerminal1->rules[2]->value = "<del|:>";
     nonTerminal1->rules[2]->num_rules = 0;
     nonTerminal1->rules[2]->rules = NULL;

     nonTerminal1->rules[3] = (struct Grammar*)malloc(sizeof(struct Grammar));
     nonTerminal1->rules[3]->is_terminal = 0;
     nonTerminal1->rules[3]->num = 4;
     nonTerminal1->rules[3]->value = (char *)malloc(LINE_SIZE * sizeof(char));
     nonTerminal1->rules[3]->value = "TIPO";
     nonTerminal1->rules[3]->num_rules = 0;
     nonTerminal1->rules[3]->rules = NULL;

     nonTerminal2 = nonTerminals[1];
     nonTerminal2->is_terminal = 0;
     nonTerminal2->num = 2;
     nonTerminal2->value = (char *)malloc(LINE_SIZE * sizeof(char));
     nonTerminal2->value = "TIPO";
     nonTerminal2->num_rules = 1;
     nonTerminal2->rules = (struct Grammar**)malloc(1 * sizeof(struct Grammar*));

     nonTerminal2->rules[0] = (struct Grammar*)malloc(sizeof(struct Grammar));
     nonTerminal2->rules[0]->is_terminal = 1;
     nonTerminal2->rules[0]->num = 1;
     nonTerminal2->rules[0]->value = (char *)malloc(LINE_SIZE * sizeof(char));
     nonTerminal2->rules[0]->value = "<inteiro>";
     nonTerminal2->rules[0]->num_rules = 0;
     nonTerminal2->rules[0]->rules = NULL;

     nonTerminal3 = nonTerminals[2];
     nonTerminal3->is_terminal = 0;
     nonTerminal3->num = 3;
     nonTerminal3->value = (char *)malloc(LINE_SIZE * sizeof(char));
     nonTerminal3->value = "TIPO";
     nonTerminal3->num_rules = 1;
     nonTerminal3->rules = (struct Grammar**)malloc(1 * sizeof(struct Grammar*));

     nonTerminal3->rules[0] = (struct Grammar*)malloc(sizeof(struct Grammar));
     nonTerminal3->rules[0]->is_terminal = 1;
     nonTerminal3->rules[0]->num = 1;
     nonTerminal3->rules[0]->value = (char *)malloc(LINE_SIZE * sizeof(char));
     nonTerminal3->rules[0]->value = "<logico>";
     nonTerminal3->rules[0]->num_rules = 0;
     nonTerminal3->rules[0]->rules = NULL;
 */
    //printf("\n%s", token->to_parse);
}

int
syntax_analysis(struct Line **program, unsigned int lncnt)
{
    int i;
    int j;
    for (i = 0; i < lncnt; ++i)
        for (j = 0; j < program[i]->numtkns; ++j)
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
     *  Allocates the memory space required for a to_parse line
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
