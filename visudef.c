//
// Created by Leonardo Fuso on 02/04/18.
//

#include "visudef.h"

int isValidID (const char *word)
{
  if (isalpha(*word)) word++;
  else
    return 0;

  if (!*word) return 1;

  return (isalnum (*word));
}

int isValidText (const char *word)
{
  return (isalnum (*word));
}

int isValidNumber (const char *word)
{
  return (isdigit (*word));
}