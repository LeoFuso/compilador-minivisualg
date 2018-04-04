//
// Created by Leonardo Fuso on 01/04/18.
//

#ifndef VISUDEF_H
#define VISUDEF_H

#include <ctype.h>

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

int isValidID (const char *);
int isValidNumber (const char *);
int isValidText (const char *);

#endif //VISUDEF_H
