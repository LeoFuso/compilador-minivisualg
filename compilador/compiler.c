//
// Created by Leonardo Fuso on 09/05/18.
//

#include "compiler.h"

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
lexical_analysis(File *);

int
syntax_analysis(struct Line **);