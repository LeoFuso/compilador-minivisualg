//
// Created by Leonardo Fuso on 09/05/18.
//

#include "stack.h"

int
is_empty(struct Node *root)
{
    return root == NULL;
}

struct Node *
new_node(char *data)
{
    struct Node *node = NULL;
    node = (struct Node *) malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void
push(struct Node **root, char *data)
{
    struct Node *node = NULL;
    node = new_node(data);
    node->next = *root;
    *root = node;
}

char *
pop(struct Node **root)
{
    if (is_empty(*root))
        return NULL;

    struct Node *temp = NULL;
    temp = *root;

    *root = (*root)->next;

    char *popped = NULL;
    popped = temp->data;

    free(temp);
    return popped;
}

char *
peek(struct Node *root)
{
    if (is_empty(root))
        return NULL;

    char *peeked = NULL;
    peeked = root->data;

    return peeked;
}