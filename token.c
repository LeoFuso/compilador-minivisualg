//
// Created by Leonardo Fuso on 04/04/18.
//

#include "token.h"

char *KEYWORDS[23] =
    {
        "VERDADEIRO",
        "FALSO",
        "var",
        "inteiro",
        "logico",
        "leia",
        "escreva",
        "escreval",
        "se",
        "entao",
        "senao",
        "fimse",
        "para",
        "de",
        "ate",
        "fimpara",
        "enquanto",
        "faca",
        "passo",
        "fimenquanto",
        "algoritmo",
        "inicio",
        "fimalgoritmo",
    };

char *OP[7] =
    {
        "+",
        "-",
        "*",
        "/",
        "mod",
        "exp",
        "<-"
    };

char *LOGIC_OP[8] =
    {
        ">",
        ">=",
        "<",
        "<=",
        "=",
        "<>",
        "e",
        "ou"
    };

char *DEL[4] =
    {
        ",",
        ":",
        "(",
        ")",
    };

int
countChar(const char *, char);

struct Token *
_idtkn(unsigned int, const char *);

struct Line *
_crtln(char *, unsigned int);

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
        if (*haystack == needle)
            ++cnt;

    return cnt;
}

struct Line *
_crtln(char *ln, unsigned int lnum)
{
    struct Line *line = NULL;

    line = malloc(sizeof(struct Line));

    /*
    * body: linha original
    * line_address: número da linha
    * tokens: lista com os tokens gerados nesta linha
    */
    line->body = ln;
    line->line_address = lnum;
    line->tokens = malloc(LINE_SIZE * sizeof(struct Token));

    return line;
}

struct Line *
_strbldr(unsigned int lnum, char *line)
{
    /*
     * Delimitadores de espaço
     */
    char *dlim_spc = " ";
    char *dlim_str = "\"";
    char *dlim = dlim_spc;

    /*
     * Token em forma de cadeia de caracteres
     */
    char *token;

    /*
     * struct Line para, mais tarde, ser jogado no arquivo de texto
     */
    struct Line *lnstrct = NULL;
    struct Token * tmptknstrct = NULL;

    unsigned int numtkns;

    lnstrct = _crtln(line, lnum);
    numtkns = 0;

    /*
     * Uma estrutura de repetição que percorre os pedaços recortados da string
     * utilizando os delimitadores de espaço como parâmetro
     */
    for (token = strtok(line, dlim); token != NULL; token = strtok(NULL, dlim))
    {
        /*
         * Verifica se dado comentário aberto, está fechado
         */
        if (countChar(token, '"') % 2 != 0)
        {
            token[strlen(token)] = ' ';
            strtok(NULL, dlim_str);
        }
        else if (strchr(token, '"') != NULL)
        {
            token[strlen(token) - 1] = '\0';
        }

        /*
         * Verificaçao de comentários na linha:
         * Tudo que está após o '//', inclusive, é ignorado
         */
        if (!strncmp(token, "//", 2))
            break;

        /*
         * Tenta criar um token a partir do pedaço da string recortada
         */
        tmptknstrct = _idtkn(lnum, token);

        /*
         * Se sucedido, insere um novo token na lista de tokens
         */
        if(tmptknstrct != NULL)
            lnstrct->tokens[numtkns++] = tmptknstrct;
        else{
            printf("Comportamento inesperado: L188token.c - encerrando...");
            exit(1);
        }
    }

    return lnstrct;
}

struct Token *
_idtkn(unsigned int lnum, const char *token)
{
    struct Token * identifiedToken;

    int i;

    for (i = 0; i < KEYWORDS_SIZE; ++i)
        if (strcmp(token, KEYWORDS[i]) == 0)
        {
            printf("         Keyword: %s\n", token);
            return identifiedToken;
        }

    for (i = 0; i < OP_SIZE; ++i)
        if (strcmp(token, OP[i]) == 0)
        {
            printf("        Operator: %s\n", token);
            return identifiedToken;
        }

    for (i = 0; i < LOGIC_OP_SIZE; ++i)
        if (strcmp(token, LOGIC_OP[i]) == 0)
        {
            printf("  Logic Operator: %s\n", token);
            return identifiedToken;
        }

    for (i = 0; i < DEL_SIZE; ++i)
        if (strcmp(token, DEL[i]) == 0)
        {
            printf("       Delimiter: %s\n", token);
            return identifiedToken;
        }

    if (!strncmp(token, "\"", 1))
    {
        token++;
        if (isValidText(token))
        {
            printf("          String: %s\n", token);
            return identifiedToken;
        }
        else
        {
            printf("    Parser error. \n");
            return identifiedToken;
        }
    }

    if (isValidID(token))
    {
        printf("              ID: %s\n", token);
        return identifiedToken;
    }

    else if (isValidNumber(token))
    {
        printf("          NUMBER: %s\n", token);
        return identifiedToken;
    }
    else
    {
        printf("    Parser error. \n");
        return identifiedToken;
    }
}

