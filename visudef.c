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
    int is_comment;
    int is_string;
    char *token = NULL;

    is_comment = is_string = 0;
    line_size = strlen(line);
    token_size = 0;

    token = malloc(line_size);

    while (line_size--)
    {
        //Preciso verificar se é o fim de uma String, A.K.A termina com '/"'
        if (is_string && *(line + token_size) == '\"')
        {
            strncpy(token, line, token_size + 1);

            line += token_size + 1;

            while (*line == ' ')
                line++;

            printf("String: %s", token);

            token_size = 0;
            is_string = 0;
        }

        //Preciso verificar se há algum comentário nessa parte do código, e ignorá-lo para o resto da linha;
        if (strncmp(line + token_size, "//", 2) == 0)
        {
            if (!is_string)
                break;
        }

        if ((*(line + token_size) == ' ' || *(line + token_size) == '\0') && is_string == 0)
        {
            strncpy(token, line, token_size);
            line += token_size;

            while (*line == ' ')
                line++;

            printf("Token: %s", token);
            token_size = 0;
        }

        if (*(line + token_size) == '\"')
            is_string = 1;
    }
}
