//
// Created by Leonardo Fuso on 01/04/18.
//

#ifndef TOKEN_H
#define TOKEN_H

#include <ctype.h>
#include <zconf.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LINE_SIZE 120
#define KEYWORDS_SIZE 21
#define OP_SIZE 7
#define LOGIC_OP_SIZE 8
#define DEL_SIZE 4

char *KEYWORDS[21] =
    {
        "VERDADEIRO",
        "FALSO",
        "inteiro",
        "logico",
        "leia",
        "escreva",
        "se",
        "entao",
        "senao",
        "fimse",
        "para",
        "de",
        "ate",
        "fimpara",
        "enquanto",
        "faca",
        "passo",
        "fimenquanto",
        "algoritmo",
        "inicio",
        "fimalgoritmo",
    };

char *OP[7] =
    {
        "+",
        "-",
        "*",
        "/",
        "mod",
        "exp",
        "<-"
    };

char *LOGIC_OP[8] =
    {
        ">",
        ">=",
        "<",
        "<=",
        "=",
        "<>",
        "e",
        "ou"
    };

char *DEL[4] =
    {
        ",",
        ":",
        "(",
        ")",
    };

typedef enum
{
    IDENTIFIER,
    KEYWORD,
    NUMBER,
    TEXT,
    LOGIC_OPERATOR,
    OPERATOR,
    DELIMITER,
    UNDEFINED,
    EOT
} TokenType;

struct Token
{
    TokenType tokenType;
    char *value;
};

struct Line
{
    int line_address;
    char *body;
    struct Token *tokens;
};

void _visualgLine(char *line);
struct Token identifyToken(const char *);
void saveToken(struct Token*);

int isValidID (const char *);
int isValidNumber (const char *);
int isValidText (const char *);

#endif //TOKEN_H
