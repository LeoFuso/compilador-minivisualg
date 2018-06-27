//
// Created by Leonardo Fuso on 09/05/18.
//

#ifndef COMPILER_H
#define COMPILER_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LINE_SIZE 120
struct Line
{
    int line_address;
    char *body;
    unsigned int numtkns;
    struct Token **tokens;
    int error;
};

struct Source
{
	struct Line ** program;
	unsigned int line_num;
	unsigned int var_num;
};

#include "token.h"
#include "syntax.h"
#include "semantic.h"

int
compile(char *);

#endif //COMPILER_H
