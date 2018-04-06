//
// Created by Leonardo Fuso on 01/04/18.
//

#ifndef TOKEN_H
#define TOKEN_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LINE_SIZE 120
#define KEYWORDS_SIZE 23
#define OP_SIZE 7
#define LOGIC_OP_SIZE 8
#define DEL_SIZE 4

typedef enum
{
    IDENTIFIER,
    KEYWORD,
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
    const char *raw;
};

struct Line
{
    int line_address;
    char *body;
    unsigned numtkns;
    struct Token **tokens;
};

struct Line *
_strbldr(unsigned int, char *);

void
saveToken(struct Token *);

int
isValidID(const char *);

int
isValidNumber(const char *);

int
isValidText(const char *);

#endif //TOKEN_H
