//
// Created by Leonardo Fuso on 02/04/18.
//

#include "visudef.h"

int
isValidID(const char *word)
{
    if (isalpha(*word))
        word++;
    else
        return 0;

    if (!*word)
        return 1;

    return (isalnum (*word));
}

int
isValidText(const char *word)
{
    return (isalnum (*word));
}

int
isValidNumber(const char *word)
{
    return (isdigit (*word));
}

int
formatLine(char *line)
{
    unsigned int token_size;
    unsigned int line_size;

    token_size = 0;
    line_size = strlen(line);

    char * token = malloc(line_size);

    while (line_size--)
    {

    }
}

