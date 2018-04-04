#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *
identifyToken(const char *token)
{
    // identifica essa besteira aí
    return "Le Tokener";
}

void
saveToken(const char *token)
{
    printf("%s\n",token);
    //printf("<%s | %s>\n", identifyToken(token), token);
}


void
_visualgLine(char *line)
{
    char *dlim_spc = " ";
    char *dlim_str = "\"";
    char *dlim = dlim_spc;
    char *token, *string_sep;

    for (token = strtok(line, dlim); token != NULL; token = strtok(NULL, dlim)) {
        if ((string_sep = strchr(token, '"')) != NULL) {
            if (dlim == dlim_spc) {
                dlim = dlim_str;
                *(strchr(string_sep, '\0')) = ' ';
            } else {
                dlim = dlim_spc;
            }
        }

        if (!strncmp(token, "//", 2))
            break;

        saveToken(token);

    }
}


int
main(int argc, char *argv[])
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
           printf ("Arquivo não encontrado.\n");
           exit (1);
         }
         break;
       default:
         printf ("Sintaxe: main [arquivo] (.visualg é implícito)\n");
         exit (0);
     }

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

    /* ---------- Aloca um espaço máximo para linhas do arquivo arbitrárias */

    unsigned int LINE_SIZE = 150;

    char *raw_line = malloc(LINE_SIZE);

    while (fgets(raw_line, LINE_SIZE, filePtr) != NULL)
    {
        *(strchr(raw_line, '\n')) = '\0';
        _visualgLine(raw_line);
    }


}
