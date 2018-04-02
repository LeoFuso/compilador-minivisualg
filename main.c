#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "visudef.h"

int
main (int argc, char *argv[])
{
  FILE *filePtr;

  char * first = "%1test";
  char * second = "test";
  char * third = "test1";

  int a = isID(first);
  printf("%d", a);
 // isID (second);
 // isID (third);


  /*--------- Tenta ler o arquivo: --------*/

  switch (argc)
  {
    case 1:

      printf ("Sintaxe: main [arquivo] (.visualg é implícito)\n");
      printf ("Nenhum arquivo fonte especificado. Encerrando...\n");
      exit (0);

    case 2:

      if ((filePtr = fopen (argv[1], "r")) == NULL && (filePtr = fopen (strcat (argv[1], ".visualg"), "r")) == NULL)
      {
        printf ("Não foi possível ler o arquivo.\n");
        exit (1);
      }

      break;

    default:

      printf ("Sintaxe: main [arquivo] (.visualg é implícito)\n");
      exit (0);

  }

  /*--------- Verifica se o arquivo está vazio: --------*/

  fseek (filePtr, 0, SEEK_END);

  if (ftell (filePtr) == 0)
  {
    printf ("Arquivo está vazio.\n");
    exit (1);
  }
  else
  {
    rewind (filePtr);
  }

  /*--------- Começa a verificar por caracteres inválidos e linhas muito compridas: --------*/

}

int isID(char* word){
  if(isalpha(word[0])) word++;
  else
    return 0;
  return (isalnum (word));
}
