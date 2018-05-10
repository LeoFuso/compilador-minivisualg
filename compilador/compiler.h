//
// Created by Leonardo Fuso on 09/05/18.
//

#ifndef COMPILER_H
#define COMPILER_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "token.h"

typedef enum
{
    IDENTIFIER,
    KEYWORD,
    BOOLEAN_OPERATOR,
    NUMBER,
    TEXT,
    LOGIC_OPERATOR,
    OPERATOR,
    DELIMITER,
    UNDEFINED
} TokenType;

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

int
compile(char *);

#endif //COMPILER_H
