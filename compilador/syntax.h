//
// Created by Leonardo Fuso on 10/05/18.
//

#ifndef SYNTAX_H
#define SYNTAX_H

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

#include "compiler.h"

int
syntax_analysis(struct Line **, unsigned int);

#endif //SYNTAX_H
