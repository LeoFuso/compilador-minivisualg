//
// Created by Leonardo Fuso on 01/04/18.
//

#ifndef TOKEN_H
#define TOKEN_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "compiler.h"

#define LINE_SIZE 120
#define KEYWORDS_SIZE 21
#define OP_SIZE 7
#define LOGIC_OP_SIZE 8
#define BOOLEAN_DATA_SIZE 2
#define DEL_SIZE 4

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

struct Line *
_strbldr(unsigned int, char *);

#endif //TOKEN_H
