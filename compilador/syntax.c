//
// Created by Leonardo Fuso on 10/05/18.
//

#include "syntax.h"


/* Number of rules */
#define GRAMMAR_HEIGHT 55

/* Max number of productions */
#define GRAMMAR_LENGTH 11

/* Height of Parsing Table */
#define NON_TERMINAL_SIZE 18

/* Length of Parsing table */
#define TERMINAL_SIZE 46

/* this is the actual size of the biggest word + '\0' character */
#define WORD_SIZE 16

#define FINAL_SYMBOL "$"
#define INITIAL_SYMBOL "A"
#define NULL_SYMBOL "&"
#define EMPTY_SYMBOL "/e/"

/*
 *
 * This is a prototype grammar, and a prototype parsing table.
 *
 * GRAMMAR_HEIGHT = 3
 * GRAMMAR_LENGTH = 11
 *
 * NON_TERMINAL_SIZE = 3
 * TERMINAL_SIZE = 5
 *
 * WORD_SIZE = 16
 *
static const char grammar[GRAMMAR_HEIGHT][GRAMMAR_LENGTH][WORD_SIZE] =
	{
		{"A", "F"},
		{"A", "<del|(>", "A", "<op|+>", "F", "<del|)>"},
		{"F", "<id>"}
	};

static const size_t grammar_ln[GRAMMAR_HEIGHT] = {2, 6, 2};

static const char table[NON_TERMINAL_SIZE][TERMINAL_SIZE][WORD_SIZE] = {
	{"&", "<del|(>", "<del|)>", "<id>", "<op|+>"},
	{"A", "1", "&", "0", "&"},
	{"F", "&", "&", "2", "&"}
};
*/

static const char grammar[GRAMMAR_HEIGHT][GRAMMAR_LENGTH][WORD_SIZE] = {
	{"A",  "<algoritmo>", "<str>", "LISTADECLAR", "<inicio>", "CODIGO", "<fimalgoritmo>", "/e/"},
	{"LISTADECLAR",  "UNIDECLAR", "LISTADECLAR"},
	{"LISTADECLAR",  "MULTIDECLAR", "LISTADECLAR"},
	{"LISTADECLAR",  "/e/"},
	{"UNIDECLAR",  "<var>", "<id>", "<del|:>", "TIPO"},
	{"MULTIDECLAR",  "IDLIST", "<del|:>", "TIPO"},
	{"TIPO",  "<inteiro>"},
	{"TIPO",  "<logico>"},
	{"IDLIST",  "<id>", "IDLIST"},
	{"IDLIST",  "<del|,>", "<id>", "IDLIST"},
	{"IDLIST",  "/e/"},
	{"CODIGO",  "COMANDO", "CODIGO"},
	{"CODIGO",  "/e/"},
	{"COMANDO",  "<id>", "<op|<->", "EXPRESSAO"},
	{"COMANDO",  "<leia>", "<del|(>", "IDLIST", "<del|)>"},
	{"COMANDO",  "<escreva>", "<del|(>", "STROUT", "<del|)>"},
	{"COMANDO",  "<se>", "EXPRESSAOLOGICA", "<entao>", "CODIGO", "<senao>", "CODIGO", "<fimse>", "/e/"},
	{"COMANDO",  "<se>", "EXPRESSAOLOGICA", "<entao>", "CODIGO", "SENAO", "<fimse>", "/e/"},
	{"COMANDO",  "<para>", "<id>", "<de>", "<num>", "<ate>", "<num>", "PASSO", "<faca>", "CODIGO", "<fimpara>", "/e/"},
	{"COMANDO",  "<enquanto>", "EXPRESSAOLOGICA", "<faca>", "CODIGO", "<fimenquanto>", "/e/"},
	{"SENAO",  "<senao>", "CODIGO"},
	{"SENAO",  "/e/"},
	{"PASSO",  "<passo>", "<num>"},
	{"PASSO",  "/e/"},
	{"EXPRESSAO",  "DATA", "OPERANDO"},
	{"OPERANDO",  "OP", "DATA"},
	{"OPERANDO",  "/e/"},
	{"STROUT",  "PRINTABLE", "STROUT"},
	{"STROUT",  "<del|,>", "PRINTABLE", "STROUT"},
	{"STROUT",  "/e/"},
	{"PRINTABLE",  "<id>"},
	{"PRINTABLE",  "<str>"},
	{"EXPRESSAOLOGICA",  "DATA", "EXPRESSAOLOGICA"},
	{"EXPRESSAOLOGICA",  "LOGICOP", "DATA", "EXPRESSAOLOGICA"},
	{"EXPRESSAOLOGICA",  "/e/"},
	{"DATA",  "<num>"},
	{"DATA",  "<str>"},
	{"DATA",  "<verdadeiro>"},
	{"DATA",  "<falso>"},
	{"DATA",  "<id>"},
	{"LOGICOP",  "<lop|>>"},
	{"LOGICOP",  "<lop|>=>"},
	{"LOGICOP",  "<lop|<>"},
	{"LOGICOP",  "<lop|<=>"},
	{"LOGICOP",  "<lop|=>"},
	{"LOGICOP",  "<lop|<>>"},
	{"LOGICOP",  "<lop|e>"},
	{"LOGICOP",  "<lop|ou>"},
	{"OP",  "<op|+>"},
	{"OP",  "<op|->"},
	{"OP",  "<op|*>"},
	{"OP",  "<op|/>"},
	{"OP",  "<op|mod>"},
	{"OP",  "<op|exp>"},
	{"OP",  "LOGICOP"}
};

static const char table[NON_TERMINAL_SIZE][TERMINAL_SIZE][WORD_SIZE] =
	{
		{"&", "<var>", "<inteiro>", "<logico>", "<leia>", "<escreva>", "<escreval>", "<se>", "<entao>", "<senao>", "<fimse>", "<para>", "<de>", "<ate>", "<fimpara>", "<enquanto>", "<faca>","<passo>", "<fimenquanto>", "<algoritmo>", "<inicio>", "<fimalgoritmo>", "<op|+>", "<op|->", "<op|*>", "<op|/>", "<op|mod>", "<op|exp>", "<op|<->", "<verdadeiro>", "<falso>", "<num>","<str>", "<del|,>", "<del|:>", "<del|(>", "<del|)>", "<lop|>>", "<lop|>=>", "<lop|<>", "<lop|<=>", "<lop|=>", "<lop|<>>", "<lop|e>", "<lop|ou>", "<id>"},
		{"A", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&"},
		{"LISTADECLAR", "0", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "2", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "1", "1", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "1"},
		{"UNIDECLAR", "3", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&","&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&"},
		{"SENAO", "&", "&", "&", "&", "&", "&", "&", "&", "19", "20", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&"},
		{"MULTIDECLAR", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "4", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "4"},
		{"TIPO", "&", "5", "6", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&","&", "&", "&", "&", "&", "&", "&", "&", "&", "&"},
		{"IDLIST", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "8", "9", "&", "9", "&", "&", "&", "&", "&", "&", "&", "&", "7"},
		{"CODIGO", "&", "&", "&", "10", "10", "&", "10", "&", "11", "11", "10", "&", "&", "11", "10", "&", "&", "11", "&", "&", "11", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "10"},
		{"COMANDO", "&", "&", "&", "13", "14", "&", "16", "&", "&", "&", "17", "&", "&", "&", "18", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "12"},
		{"PASSO", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "22", "21", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&"},
		{"EXPRESSAO", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "23", "23", "23", "23", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "23"},
		{"OPERANDO", "&", "&", "&", "25", "25", "&", "25", "&", "25", "25", "25", "&", "&", "25", "25", "&", "&", "25", "&", "&", "25", "24", "24", "24", "24", "24", "24", "&", "&", "&", "&","&", "&", "&", "&", "&", "24", "24", "24", "24", "24", "24", "24", "24", "25"},
		{"STROUT", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "26", "27", "&", "&", "28", "&", "&", "&", "&", "&", "&", "&", "&", "26" },
		{"PRINTABLE", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "30", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "29" },
		{"EXPRESSAOLOGICA", "&", "&", "&", "&", "&", "&", "&", "33", "&", "&", "&", "&", "&", "&", "&", "33", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "31", "31", "31", "31", "&", "&", "&", "&", "32", "32", "32", "32", "32", "32", "32", "32", "31" },
		{"DATA", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "36", "37", "34", "35", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "38" },
		{"LOGICOP", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "39", "40", "41", "42", "43", "44", "45", "46", "&" },
		{"OP", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "47", "48", "49", "50", "51", "52", "&", "&", "&", "&", "&", "&", "&", "&", "&", "53", "53", "53", "53", "53", "53", "53", "53", "&" }

	};

static const size_t grammar_ln[GRAMMAR_HEIGHT] =
	 {8, 3, 3, 2, 5, 4, 2, 2, 3, 4, 2, 3, 2, 4, 5, 5, 9, 8, 12, 7, 3, 2, 3, 2, 3, 3, 2, 3, 4, 2, 2, 2, 3, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

static struct Node *stack = NULL;

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
	push(&stack, FINAL_SYMBOL);
	push(&stack, INITIAL_SYMBOL);

	int i;
	int j;
	for (i = 0; i < lncnt; ++i)
		for (j = 0; j < program[i]->numtkns;)
			if (_parse(program[i]->tokens[j]))
				j++;

	final = peek(stack);
	return !strcmp(final, FINAL_SYMBOL);
}

int
_parse(struct Token *source)
{
	char *current = (char *) malloc(WORD_SIZE * sizeof(char));
	char *top = NULL;
	char **prod_elements = NULL;

	strcpy(current, source->to_parse);
	top = pop(&stack);

	while (strcmp(top, EMPTY_SYMBOL) == 0)
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
	for (i = 1; i < TERMINAL_SIZE; ++i)
		if (strcmp(to_check, table[0][i]) == 0)
			return i;
	return 0;
}

char **
_getProd(char *non_terminal, char *terminal)
{
	int rule_num;

	char *str_rule_num = (char *) malloc(WORD_SIZE * sizeof(char));
	char **stack = NULL;
	int i_non_terminal = _getIndex(non_terminal, 0);
	int i_terminal = _getIndex(terminal, 1);

	if (!i_non_terminal)
	{
		printf("\nError. Non Terminal Word '%s' not found in Production Table.\nThis is not a valid program. Closing...",
		       non_terminal);
		exit(1);
	}
	if (!i_terminal)
	{
		printf("\nError. Terminal Word '%s' not found in Production Table.\nThis is not a valid program. Closing...",
		       terminal);
		exit(1);
	}

	strcpy(str_rule_num, table[i_non_terminal][i_terminal]);

	if (strcmp(NULL_SYMBOL, str_rule_num) == 0)
	{
		printf(
			"\nError. Rule for Non Terminal Word '%s' and Terminal Word '%s' not found in in Production Table.\nThis is not a valid program. Closing...",
			non_terminal,
			terminal);
		exit(1);
	}

	/* 10 is the numerical base for conversion */
	rule_num = (int) strtol(str_rule_num, (char **) NULL, 10);

	stack = _getProdOrigin(rule_num);

	if (!stack)
	{
		printf("\nError. Rule '%d' not found in grammar.\nThis is not a valid program. Closing...", rule_num);
		exit(1);
	}

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
		for (i = 1; i < TERMINAL_SIZE; ++i)
			if (strcmp(find, table[0][i]) == 0)
				return i;
	}
	else
	{
		for (i = 1; i < NON_TERMINAL_SIZE; ++i)
			if (strcmp(find, table[i][0]) == 0)
				return i;
	}
	return 0;
}