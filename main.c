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
verify(char *piece)
{
    int i = 0;
    printf("\n");
    printf(piece);
    /*for (i = 0; i < KEYWORDS_SIZE; i++)
    {
        if (strcmp(piece, KEYWORDS[i]) == 0)
        {
            printf("\n");
            printf(KEYWORDS[i]);
            printf("  -  MATCHES!\n");
        }
    }*/
}

void
loop(char *word, size_t length)
{
    size_t count = 0;
    /*while (length--)
    {

        check(word, count);
        count++;
    }*/

    while (*word != '\0') // Até o fim da linha
    {

        if (*(word - 1) == ' ' && *(word + 1) != '\0')
        { // If previous is space and next letter exists
            printf("%c", *word);      // take it save it or print it
        }
        word++; //proceed
    }
}

void
read_line(char *line, size_t length)
{
    size_t count = 0;

    char *toCompare;
    int isCommentary = 0;
    int isString = 0;

    while (length--) // Até o fim da linha
    {

        if (isString && *(line + count) == '\"') // Procura pela última ocorrência de \" para verificar uma String
        {
            toCompare = malloc(count+1);
            strncpy(toCompare, line, count+1);

            for (int i = 0; i < count+1; i++)
                line++;

            verify(toCompare);
            count = 0;

            while (*line == ' ')
                line++;

            isString = 0;

        }

        if (*(line + count) == '/' && *(line + count + 1) == '/')
        {
            isCommentary = 1;
        }

        if ((*(line + count) == ' ' || *(line + count) == '\0' || *(line + count) == '\n') && isCommentary == 0 && isString == 0)
        {
            toCompare = malloc(count);
            strncpy(toCompare, line, count);

            for (int i = 0; i < count; i++)
                line++;

            verify(toCompare);
            count = 0;

            while (*line == ' ')
                line++;
        }

        if (*(line + count) == '\"')
        {
            if (!isCommentary)
            {
                isString = 1;
            }
        }

        count++;
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

    //fgets(ordinary_line, LINE_SIZE, filePtr);

    while (fgets(ordinary_line, LINE_SIZE, filePtr) != NULL)
    {
        read_line(ordinary_line, strlen(ordinary_line));
    }

    // printf(ordinary_line);

    // loop(ordinary_line, strlen(ordinary_line));



    /*--------- Começa a verificar por caracteres inválidos e linhas muito compridas: --------*/

}
