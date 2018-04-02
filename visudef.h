//
// Created by Leonardo Fuso on 01/04/18.
//

#ifndef VISUDEF_H
#define VISUDEF_H

#include <ctype.h>

/*
#define LINE_SIZE 120
#define TEXT_PATTERN "^[A-Za-z0-9]*$"
#define NUMBER_PATTERN "^[0-9]*$"
#define IDENTIFIER_PATTERN "^([a-zA-Z_][a-zA-Z0-9]+)"
*/


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
        "faca",
        "fimpara",
        "enquanto",
        "faca",
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

int isID(char*);
int isNumber(char*);
int isText(char*);

#endif //VISUDEF_H
