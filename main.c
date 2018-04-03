#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "visudef.h"

int
check(char *piece, size_t count)
{
    int matches = 0;
    int i;
    char *destination = malloc(count + 1);
    strncpy(destination, piece, count);

    printf("%s\n", destination);

    for (i = 0; i < KEYWORDS_SIZE; i++)
    {
        if (strcmp(destination, KEYWORDS[i]) == 0)
        {
            printf("MATCHES!\n");
        }
    }

}

void
loop(char *word, size_t length)
{
    size_t count = 0;
    while (length--)
    {

        check(word, count);
        count++;
    }

    while (*word != '\0') // Até o fim da linha
    {

        if (*(word - 1) == ' ' && *(word + 1) != '\0')
        { // If previous is space and next letter exists
            printf("%c", *word);      // take it save it or print it
        }
        word++; //proceed
    }
}

int
main(int argc, char *argv[])
{
    FILE *filePtr = fopen("/home/lfuso/Repository/compilador-minivisualg/salario.visualg", "r");

    /*--------- Tenta ler o arquivo: --------*/

    /*
     switch (argc)
     {
       case 1:

         printf ("Sintaxe: main [arquivo] (.visualg é implícito)\n");
         printf ("Nenhum arquivo fonte especificado. Encerrando...\n");
         exit (0);

       case 2:

         if ((filePtr = fopen (argv[1], "r")) == NULL && (filePtr = fopen (strcat (argv[1], ".visualg"), "r")) == NULL)
         {
           printf ("Arquivo não encontrado.\n");
           exit (1);
         }

         break;

       default:

         printf ("Sintaxe: main [arquivo] (.visualg é implícito)\n");
         exit (0);

     }
   */

    /*--------- Verifica se o arquivo está vazio: --------*/

    fseek(filePtr, 0, SEEK_END);

    if (ftell(filePtr) == 0)
    {
        printf("Arquivo está vazio.\n");
        exit(1);
    }
    else
    {
        rewind(filePtr);
    }

    //Testing things out

    char *ordinary_line = malloc(LINE_SIZE);

    fgets(ordinary_line, LINE_SIZE, filePtr);

    printf(ordinary_line);

    loop(ordinary_line, strlen(ordinary_line));


    /*--------- Começa a verificar por caracteres inválidos e linhas muito compridas: --------*/

}
