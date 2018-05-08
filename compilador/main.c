#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

int
main(int argc, char *argv[])
{

    FILE *filePtr;
    FILE *fileOut;

    unsigned int lncnt = 0;
    char *raw_line = NULL;
    struct Line **program = NULL;
    struct Line *lncomplete = NULL;

    /*
     *  Tenta ler o arquivo
     */
    switch (argc)
    {
        case 1:printf("Sintaxe: main [arquivo] (.visualg eh implicito)\n");
            printf("Nenhum arquivo fonte especificado. Encerrando...\n");
            exit(0);
        case 2:
            if ((filePtr = fopen(argv[1], "r")) == NULL && (filePtr = fopen(strcat(argv[1], ".visualg"), "r")) == NULL)
            {
                printf("Arquivo não encontrado.\n");
                exit(1);
            }
            break;
        default:printf("Sintaxe: main [arquivo] (.visualg e implicito)\n");
            exit(0);
    }

    /*
     *  Verifica se o arquivo esta vazio
     */
    fseek(filePtr, 0, SEEK_END);

    if (ftell(filePtr) == 0)
    {
        printf("Arquivo esta vazio.\n");
        exit(1);
    }
    else
    {
        rewind(filePtr);
    }

    printf("\n---------------------------------------------------------------------------------\n\n");
    printf("Arquivo de nome '%s' aberto com sucesso.\n", argv[1]);


    /*
     *  Aloca o espaço de memoria necessario para uma linha do codigo-fonte
     */
    raw_line = (char *) malloc(LINE_SIZE * sizeof(char) + 1);

    /*
     * Conta quantas linhas o arquivo tem
     */
    while (fgets(raw_line, LINE_SIZE, filePtr) != NULL)
        lncnt++;


    /*
     * Rebobina o arquivo
     */
    rewind(filePtr);

    /*
     * Aloca o espaco de memoria necessario para todo o programa
     */
    program = (struct Line **) malloc(lncnt * (sizeof(struct Line *)));
    lncnt = 0;

    printf("\n---------------------------------------------------------------------------------\n\n");
    printf("Tokens identificados:\n\n\n");

    /*
     *  Percorre as linhas do arquivo, uma a uma, produzindo Tokens
     */
    unsigned int lnum;
    for (lnum = 1; (fgets(raw_line, LINE_SIZE, filePtr) != NULL); ++lnum)
    {
        /*
        * Faz a troca do '\n' por '\0'
        */
        if (strchr(raw_line, '\n') != NULL)
            *(strchr(raw_line, '\n')) = '\0';

        /*
         * Monta os Tokens usando as informacoes da linha
         */
        lncomplete = _strbldr(lnum, raw_line);

        if (lncomplete != NULL)
            program[lncnt++] = lncomplete;
        else
        {
            printf("Comportamento inesperado: L104main.c - encerrando...");
            exit(1);
        }

        if (lncomplete->error != 0)
            break;
    }

    printf("\n---------------------------------------------------------------------------------\n\n");
    printf("-- Gravando no arquivo --\n");

    fileOut = fopen(strcat(argv[1], ".token"), "w");

    /*
     * Verifica se arquivo de saida foi criado
     */
    if (fileOut == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }

    int i;
    int j;
    for (i = 0; i < lncnt; i++)
    {
        for (j = 0; j < program[i]->numtkns; j++)
            fprintf(fileOut, "%s", program[i]->tokens[j]->body);
        fprintf(fileOut, "\n");
    }

    printf("\n---------------------------------------------------------------------------------\n\n\n");
    printf("\nSucesso.\n\nOs tokens foram criados no arquivo '%s' \ndeste mesmo diretorio.\n\n\n", argv[1]);

    /*
     * Encerra os arquivos
     */
    fclose(filePtr);
    fclose(fileOut);
}