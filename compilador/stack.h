//
// Created by Leonardo Fuso on 09/05/18.
//

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/* A structure to represent a stack */
struct Node
{
    char * data;
    struct Node* next;
};

void
push(struct Node **, char *);

char *
pop(struct Node **);

char *
peek(struct Node *);

#endif //STACK_H
