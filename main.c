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
        case 1:printf("Sintaxe: main [arquivo] (.visualg é implícito)\n");
            printf("Nenhum arquivo fonte especificado. Encerrando...\n");
            exit(0);
        case 2:
            if ((filePtr = fopen(argv[1], "r")) == NULL && (filePtr = fopen(strcat(argv[1], ".visualg"), "r")) == NULL)
            {
                printf("Arquivo não encontrado.\n");
                exit(1);
            }
            break;
        default:printf("Sintaxe: main [arquivo] (.visualg é implícito)\n");
            exit(0);
    }

    /*
     *  Verifica se o arquivo está vazio
     */
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

    printf("\n---------------------------------------------------------------------------------\n\n");
    printf("Arquivo de nome '%s' aberto com sucesso.\n",argv[1]);


    /*
     *  Aloca o espaço de memória necessário para uma linha do código-fonte
     */
    raw_line = malloc(LINE_SIZE * sizeof(char));

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
     * Aloca o espaço de memória necessário para todo o programa
     */
    program = (struct Line **) malloc(lncnt * (sizeof(struct Line *)));
    lncnt = 0;

    printf("\n---------------------------------------------------------------------------------\n\n");
    printf("Tokens identificados:\n\n\n");


    /*
     *  Percorre as linhas do arquivo, uma a uma, produzindo Tokens
     */
    for (unsigned int lnum = 1; (fgets(raw_line, LINE_SIZE, filePtr) != NULL); ++lnum)
    {
        /*
         * Faz a troca do '\n' por '\0'
         */
        *(strchr(raw_line, '\n')) = '\0';

        /*
         * Monta os Tokens usando as informações da linha
         */
        lncomplete = _strbldr(lnum, raw_line);

        if (lncomplete != NULL)
            program[lncnt++] = lncomplete;
        else
        {
            printf("Comportamento inesperado: L88main.c - encerrando...");
            exit(1);
        }
    }


    printf("\n---------------------------------------------------------------------------------\n\n");
    printf("-- Gravando no arquivo --\n");

    fileOut = fopen(strcat(argv[1], ".token"), "w");

    /*
     * Verifica se arquivo de saída foi criado
     */
    if (fileOut == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }

    for (int i = 0; i < lncnt; i++)
    {
        for (int j = 0; j < program[i]->numtkns; j++)
            fprintf(fileOut, "%s", program[i]->tokens[j]->value);
        fprintf(fileOut, "\n");
    }

    printf("\n---------------------------------------------------------------------------------\n\n\n");
    printf("\nSucesso.\n\nOs tokens foram criados no arquivo '%s' \ndeste mesmo diretório.\n\n\n", argv[1]);


    /*
     * Encerra os arquivos
     */
    fclose(filePtr);
    fclose(fileOut);
}
