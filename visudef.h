//
// Created by Leonardo Fuso on 01/04/18.
//

#ifndef VISUDEF_H
#define VISUDEF_H

#define LINE_SIZE 120

typedef enum {
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

char *OP[6] =
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

typedef struct {
    TokenType tokenType;
    char *value;
    int line_address;
};

#endif //VISUDEF_H
