//
// Created by Leonardo Fuso on 10/05/18.
//

#include "syntax.h"

#define len(X) (sizeof(X)/sizeof(X[0]))

static const char grammar[3][11][16] =
    {
        {"A", "F"},
        {"A", "<del|(>", "A", "<op|+>", "F", "<del|)>"},
        {"F", "<id>"}
    };

static const size_t grammar_ln[3] = {2, 6, 2};

static const char table[3][5][16] = {
    {"&", "<del|(>", "<del|)>", "<id>", "<op|+>"},
    {"A", "1", "&", "0", "&"},
    {"F", "&", "&", "2", "&"}
};


/*
static const char grammar2[52][11][16] = {
    {"A", "<algoritmo>", "<str>", "LISTADECLAR", "<inicio>", "CODIGO", "<fimalgoritmo>"},
    {"LISTADECLAR", "UNIDECLAR", "LISTADECLAR"},
    {"LISTADECLAR", "MULTIDECLAR", "LISTADECLAR"},
    {"LISTADECLAR", "/e/"},
    {"UNIDECLAR", "<var>", "<id>", "<del|:>", "TIPO"},
    {"MULTIDECLAR", "IDLIST", "<del|:>", "TIPO"},
    {"TIPO", "<inteiro>"},
    {"TIPO", "<logico>"},
    {"IDLIST", "<id>", "IDLIST"},
    {"IDLIST", "<del|,>", "<id>", "IDLIST"},
    {"IDLIST", "/e/"},
    {"CODIGO", "COMANDO", "CODIGO"},
    {"CODIGO", "/e/"},
    {"COMANDO", "<id>", "<op|<->", "EXPRESSAO"},
    {"COMANDO", "<leia>", "<del|(>", "IDLIST", "<del|)>"},
    {"COMANDO", "<escreva>", "<del|(>", "STROUT", "<del|)>"},
    {"COMANDO", "<se>", "EXPRESSAOLOGICA", "<entao>", "CODIGO", "<senao>", "CODIGO", "<fimse>"},
    {"COMANDO", "<para>", "<id>", "<de>", "<num>", "<ate>", "<num>", "PASSO", "<faca>", "CODIGO",
     "<fimpara>"},
    {"COMANDO", "<enquanto>", "EXPRESSAOLOGICA", "<faca>", "CODIGO", "<fimenquanto>"},
    {"PASSO", "<passo>", "<num>"},
    {"PASSO", "/e/"},
    {"EXPRESSAO", "DATA", "OPERANDO"},
    {"OPERANDO", "OP", "DATA"},
    {"OPERANDO", "/e/"},
    {"STROUT", "PRINTABLE", "STROUT"},
    {"STROUT", "<del|,>", "PRINTABLE", "STROUT"},
    {"STROUT", "/e/"},
    {"PRINTABLE", "<id>"},
    {"PRINTABLE", "<str>"},
    {"EXPRESSAOLOGICA", "DATA", "EXPRESSAOLOGICA"},
    {"EXPRESSAOLOGICA", "LOGICOP", "DATA", "EXPRESSAOLOGICA"},
    {"EXPRESSAOLOGICA", "/e/"},
    {"DATA", "<num>"},
    {"DATA", "<str>"},
    {"DATA", "<verdadeiro>"},
    {"DATA", "<falso>"},
    {"DATA", "<id>"},
    {"LOGICOP", "<lop|>>"},
    {"LOGICOP", "<lop|>=>"},
    {"LOGICOP", "<lop|<>"},
    {"LOGICOP", "<lop|<=>"},
    {"LOGICOP", "<lop|=>"},
    {"LOGICOP", "<lop|<>>"},
    {"LOGICOP", "<lop|e>"},
    {"LOGICOP", "<lop|ou>"},
    {"OP", "<op|+>"},
    {"OP", "<op|->"},
    {"OP", "<op|*>"},
    {"OP", "<op|/>"},
    {"OP", "<op|mod>"},
    {"OP", "<op|exp>"},
    {"OP", "LOGICOP"}
};
*/


/*
static const char table2[18][45][16] =
    {
        {NULL, "<var>", "<inteiro>", "<logico>", "<leia>", "<escreva>", "<escreval>", "<se>", "<entao>", "<senao>",
         "<fimse>", "<para>", "<de>", "<ate>", "<fimpara>", "<enquanto>", "<faca>", "<passo>", "<fimenquanto>",
         "<algoritmo>", "<inicio>", "<fimalgoritmo>", "<op|+>", "<op|->", "<op|*>", "<op|/>", "<op|mod>", "<op|exp>",
         "<op|<->", "<verdadeiro>", "<falso>", "<num>", "<str>", "<del|,>", "<del|:>", "<del|(>", "<del|)>", "<lop|>>",
         "<lop|>=>", "<lop|<>", "<lop|<=>", "<lop|=>", "<lop|<>>", "<lop|e>", "<lop|ou>", "<id>"},
        {"A", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, "0", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {"LISTADECLAR", "1", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, "3", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "2", "2", NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "2"},
        {"UNIDECLAR", "4", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {"MULTIDECLAR", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "5", NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "5"},
        {"TIPO", NULL, "6", "7", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {"IDLIST", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "9", "10", NULL,
         "10", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "8"},
        {"CODIGO", NULL, NULL, NULL, "11", "11", NULL, "11", NULL, "12", "12", "11", NULL, NULL, "12", "11", NULL, NULL,
         "12", NULL, NULL, "12", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "11"},
        {"COMANDO", NULL, NULL, NULL, "14", "15", NULL, "16", NULL, NULL, NULL, "17", NULL, NULL, NULL, "18", NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "13"},
        {"PASSO", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "20", "19",
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {"EXPRESSAO", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "21", "21", "21", "21", NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "21"},
        {"OPERANDO", NULL, NULL, NULL, "23", "23", NULL, "23", NULL, "23", NULL, "23", NULL, NULL, "23", "23", NULL,
         NULL, "23", NULL, NULL, "23", "22", "22", "22", "22", "22", "22", NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, "22", "22", "22", "22", "22", "22", "22", "22", "23"},
        {"STROUT", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "24", "25", NULL, NULL,
         "26", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "24"},
        {"PRINTABLE", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "28", NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "27"},
        {"EXPRESSAOLOGICA", NULL, NULL, NULL, NULL, NULL, NULL, NULL, "31", NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         "31", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "29", "29", "29", "29", NULL,
         NULL, NULL, NULL, "30", "30", "30", "30", "30", "30", "30", "30", "29"},
        {"DATA", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "34", "35", "32", "33", NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "36"},
        {"LOGICOP", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, "37", "38", "39", "40", "41", "42", "43", "44", NULL},
        {"OP", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, "45", "46", "47", "48", "49", "50", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, "51", "51", "51", "51", "51", "51", "51", "51", NULL}
    };

static const size_t grammar_ln[52] =
    {7, 3, 3, 2, 5, 4, 2, 2, 3, 4, 2, 3, 2, 4, 5, 5, 8, 11, 6, 3, 2, 3, 3, 2, 3, 4, 2, 2, 2, 3, 4, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
*/


static const unsigned int num_terminals = 5;
static const unsigned int num_nonterminals = 3;

/*
static const unsigned int num_nonterminals = 18;
static const unsigned int num_terminals = 45;
*/

static struct Node *stack = NULL;
static const char *EMPTY = "/e/";

int
print_grammar(void)
{
    int i;
    int j;
    for (i = 0; i < len(grammar); i++)
        for (j = 0; j < grammar_ln[i]; ++j)
            printf("\n%s", grammar[i][j]);

    return 0;
}

void
_stck(struct Token *);

int
_parse(struct Token *);

int
_isterminal(char *);

char **
_getProd(char *, char *);

int
_getIndex(char *, int);

char **
_getProdOrigin(int);

int
syntax_analysis(struct Line **program, unsigned int lncnt)
{
    int f_parse;
    push(&stack, "$");
    push(&stack, "A");

//    printf("%s popped from stack\n", pop(&stack));
    printf("Top element is %s\n", peek(stack));

    print_grammar();
    int i;
    int j;
    for (i = 0; i < lncnt; ++i)
        for (j = 0; j < program[i]->numtkns; ++j)
            if (_parse(program[i]->tokens[j]))
                --j;

    return 1;
}

int
_parse(struct Token *source)
{
    char *current = (char *) malloc(16 * sizeof(char));
    char *top = NULL;
    char **prod_elements = NULL;

    strcpy(current, source->to_parse);
    top = pop(&stack);

    while (strcmp(top, EMPTY) == 0)
        top = pop(&stack);

    if (_isterminal(top) && (strcmp(top, current) == 0))
        return 0;
    else
        prod_elements = _getProd(top, current);

    printf("\nProd elements: ");
    int prod_elements_num;
    for (prod_elements_num = 0; prod_elements[prod_elements_num] != NULL; prod_elements_num++)
        printf("\n%s", prod_elements[prod_elements_num]);

    int i;
    for (i = prod_elements_num - 1; i > 0; i--)
    {
        printf("\n%s pushed to stack", prod_elements[i]);
        push(&stack, prod_elements[i]);
    }

    return 1;
}

int
_isterminal(char *to_check)
{
    unsigned int i;
    for (i = 1; i < num_terminals; ++i)
        if (strcmp(to_check, table[0][i]) == 0)
            return i;
    return 0;
}

char **
_getProd(char *non_terminal, char *terminal)
{
    int rulenum;

    char *str_rule_num = (char *) malloc(16 * sizeof(char));
    char **stack = NULL;
    int i_non_terminal = _getIndex(non_terminal, 0);
    int i_terminal = _getIndex(terminal, 1);

    if ((!i_non_terminal) || (!i_terminal))
        exit(1);

    strcpy(str_rule_num, table[i_non_terminal][i_terminal]);

    if (strcmp("&", str_rule_num) == 0)
        exit(1);

    rulenum = (int) strtol(str_rule_num, (char **) NULL, 10);

    stack = _getProdOrigin(rulenum);

    if (!stack)
        exit(1);

    return stack;
}

char **
_getProdOrigin(int rule_num)
{
    char **rule = NULL;
    const size_t rule_num_size = grammar_ln[rule_num];
    rule = (char **) calloc(rule_num_size, sizeof(char *));

    unsigned int i;
    for (i = 1; i < rule_num_size; i++)
        rule[i - 1] = strdup(grammar[rule_num][i]);

    return rule;
}

int
_getIndex(char *find, int t)
{
    unsigned int i;
    if (t)
    {
        for (i = 1; i < num_terminals; ++i)
            if (strcmp(find, table[0][i]) == 0)
                return i;
    }
    else
    {
        for (i = 1; i < num_nonterminals; ++i)
            if (strcmp(find, table[i][0]) == 0)
                return i;
    }
    return 0;
}

void
_stck(struct Token *tkn)
{
    //printf("\n%s", tkn->to_parse);
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
