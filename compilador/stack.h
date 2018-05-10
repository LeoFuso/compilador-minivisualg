//
// Created by Leonardo Fuso on 09/05/18.
//

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// A structure to represent a stack
struct StackNode
{
    struct Token * data;
    struct StackNode* next;
};

struct StackNode* new_node(struct Token * data);

#endif //STACK_H
