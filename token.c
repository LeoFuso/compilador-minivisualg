//
// Created by Leonardo Fuso on 04/04/18.
//

#include "token.h"

int countChar(const char *, char);

int
isValidID(const char *word)
{
    if (isalpha(*word))
        word++;
    else
        return 0;

    if (!*word)
        return 1;

    return (isalnum(*word));
}

int
isValidText(const char *word)
{
    return (isalnum(*word));
}

int
isValidNumber(const char *word)
{
    return (isdigit(*word));
}

int
countChar(const char *haystack, char needle)
{
    unsigned int cnt = 0;

    for (; *haystack != '\0'; ++haystack)
        if (*haystack == needle) ++cnt;

    return cnt;
}

void
_visualgLine(char *line)
{
    char *dlim_spc = " ";
    char *dlim_str = "\"";
    char *dlim = dlim_spc;
    char *token;

    for (token = strtok(line, dlim); token != NULL; token = strtok(NULL, dlim))
    {
        if (countChar(token, '"') % 2 != 0)
        {
            token[strlen(token)] = ' ';
            strtok(NULL, dlim_str);
        }
        else if (strchr(token, '"') != NULL)
        {
            token[strlen(token) - 1] = '\0';
        }

        if (!strncmp(token, "//", 2))
            break;

        identifyToken(token);

    }
}

struct Token
identifyToken(const char *token)
{
    printf("%s\n", token);
}

