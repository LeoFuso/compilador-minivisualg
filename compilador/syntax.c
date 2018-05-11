//
// Created by Leonardo Fuso on 10/05/18.
//

#include "syntax.h"

void
_stck(struct Token *);

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

void
_stck(struct Token * tkn)
{
    printf("\n%s",tkn->to_parse);
}

/*

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
lol(struct Token *token)
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

            */
/*
             *  It does the exchange of '\n' for '\0'
             *//*

            if (strchr(raw_line, '\n') != NULL)
                *(strchr(raw_line, '\n')) = '\0';

            type_list[lnum] = raw_line;
            printf("\n%s", type_list[lnum]);

        }

    }


    */
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
 *//*

    //printf("\n%s", token->to_parse);
}*/
