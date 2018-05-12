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

static const unsigned int num_terminals = 5;
static const unsigned int num_non_terminals = 3;
/*
static const char grammar[52][11][16] = {
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

static const char table[18][46][16] =
    {

   m""                #                "                                               "             m
 mm#mm  m   m   mmm   #   m          mmm    mmm   m   m   mmm    mmm    mmm    m mm  mmm    mmmm   mm#mm
   #    #   #  #"  "  # m"             #   "   #  "m m"  "   #  #   "  #"  "   #"  "   #    #" "#    #
   #    #   #  #      #"#              #   m"""#   #m#   m"""#   """m  #       #       #    #   #    #
   #    "mm"#  "#mm"  #  "m            #   "mm"#    #    "mm"#  "mmm"  "#mm"   #     mm#mm  ##m#"    "mm
                                       #                                                    #
                                     ""                                                     "
        {"&", "<var>", "<inteiro>", "<logico>", "<leia>", "<escreva>", "<escreval>", "<se>", "<entao>", "<senao>",
         "<fimse>", "<para>", "<de>", "<ate>", "<fimpara>", "<enquanto>", "<faca>", "<passo>", "<fimenquanto>",
         "<algoritmo>", "<inicio>", "<fimalgoritmo>", "<op|+>", "<op|->", "<op|*>", "<op|/>", "<op|mod>", "<op|exp>",
         "<op|<->", "<verdadeiro>", "<falso>", "<num>", "<str>", "<del|,>", "<del|:>", "<del|(>", "<del|)>", "<lop|>>",
         "<lop|>=>", "<lop|<>", "<lop|<=>", "<lop|=>", "<lop|<>>", "<lop|e>", "<lop|ou>", "<id>"},
        {"A", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "0", "&", "&",
         "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&"},
        {"LISTADECLAR", "1", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "3", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "2", "2", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "2"},
        {"UNIDECLAR", "4", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "&"},
        {"MULTIDECLAR", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "5", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "5"},
        {"TIPO", "&", "6", "7", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&"},
        {"IDLIST", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "9", "10", "&", "10", "&", "&", "&", "&", "&", "&",
         "&", "&", "8"},
        {"CODIGO", "&", "&", "&", "11", "11", "&", "11", "&", "12", "12", "11", "&", "&", "12", "11", "&", "&", "12",
         "&", "&", "12", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "&", "11"},
        {"COMANDO", "&", "&", "&", "14", "15", "&", "16", "&", "&", "&", "17", "&", "&", "&", "18", "&", "&", "&", "&",
         "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "13"},
        {"PASSO", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "20", "19", "&", "&", "&",
         "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&"},
        {"EXPRESSAO", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "&", "&", "&", "&", "&", "&", "21", "21", "21", "21", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "&", "21"},
        {"OPERANDO", "&", "&", "&", "23", "23", "&", "23", "&", "23", "&", "23", "&", "&", "23", "23", "&", "&", "23",
         "&", "&", "23", "22", "22", "22", "22", "22", "22", "&", "&", "&", "&", "&", "&", "&", "&", "&", "22", "22",
         "22", "22", "22", "22", "22", "22", "23"},
        {"STROUT", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "24", "25", "&", "&", "26", "&", "&", "&", "&", "&",
         "&", "&", "&", "24"},
        {"PRINTABLE", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "28", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "27"},
        {"EXPRESSAOLOGICA", "&", "&", "&", "&", "&", "&", "&", "31", "&", "&", "&", "&", "&", "&", "&", "31", "&", "&",
         "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "29", "29", "29", "29", "&", "&", "&", "&", "30", "30", "30",
         "30", "30", "30", "30", "30", "29"},
        {"DATA", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "&", "&", "&", "&", "&", "34", "35", "32", "33", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "36"},
        {"LOGICOP", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "37", "38", "39", "40", "41",
         "42", "43", "44", "&"},
        {"OP", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&",
         "45", "46", "47", "48", "49", "50", "&", "&", "&", "&", "&", "&", "&", "&", "&", "51", "51", "51", "51", "51",
         "51", "51", "51", "&"}

    };

static const size_t grammar_ln[52] =
    {7, 3, 3, 2, 5, 4, 2, 2, 3, 4, 2, 3, 2, 4, 5, 5, 8, 11, 6, 3, 2, 3, 3, 2, 3, 4, 2, 2, 2, 3, 4, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

static const unsigned int num_non_terminals = 18;
static const unsigned int num_terminals = 45;*/

static struct Node *stack = NULL;
static const char *EMPTY = "/e/";
static const char *FINAL = "$";
static const char *NULL_CHAR = "&";

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
    char *final = NULL;
    push(&stack, "$");
    push(&stack, "A");

    int i;
    int j;
    for (i = 0; i < lncnt; ++i)
        for (j = 0; j < program[i]->numtkns;)
            if (_parse(program[i]->tokens[j]))
                j++;

    final = peek(stack);
    return !strcmp(final, FINAL);
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
        return 1;
    else
        prod_elements = _getProd(top, current);

    int prod_elements_num;
    for (prod_elements_num = 0; prod_elements[prod_elements_num] != NULL; prod_elements_num++);

    int i;
    for (i = prod_elements_num - 1; i >= 0; i--)
        push(&stack, prod_elements[i]);

    return 0;
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
    int rule_num;

    char *str_rule_num = (char *) malloc(16 * sizeof(char));
    char **stack = NULL;
    int i_non_terminal = _getIndex(non_terminal, 0);
    int i_terminal = _getIndex(terminal, 1);

    if ((!i_non_terminal) || (!i_terminal))
        exit(1);

    strcpy(str_rule_num, table[i_non_terminal][i_terminal]);

    if (strcmp(NULL_CHAR, str_rule_num) == 0)
        exit(1);

    rule_num = (int) strtol(str_rule_num, (char **) NULL, 10);

    stack = _getProdOrigin(rule_num);

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
        for (i = 1; i < num_non_terminals; ++i)
            if (strcmp(find, table[i][0]) == 0)
                return i;
    }
    return 0;
}
