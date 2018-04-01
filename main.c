#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main (int argc, char *argv[])
{
  FILE *filePtr;

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