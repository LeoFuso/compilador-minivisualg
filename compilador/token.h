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

struct Line *
_strbldr(unsigned int, char *);

int
is_valid_id(const char *);

int
is_valid_num(const char *);

int
is_valid_txt(const char *);

#endif //TOKEN_H
