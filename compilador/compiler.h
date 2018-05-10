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
    const char *to_parse;
};

struct Line
{
    int line_address;
    char *body;
    unsigned int numtkns;
    struct Token **tokens;
    int error;
};

struct Table
{
    unsigned int numNonTerminals;
    struct NonTerminal **nonTerminals;
};

struct Grammar
{
    unsigned int is_terminal;
    unsigned int num;
    char *value;

    unsigned int num_rules;
    struct Grammar **rules;
};

struct NonTerminal
{
    unsigned int num_rule;
    char *non_terminal;
    unsigned int num_terminals;
    struct Terminal **terminals;
};

struct Terminal
{
    const unsigned int number;
    const char *value;
};

int
compile(char *);

#endif //COMPILER_H
