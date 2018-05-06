//
// Created by Leonardo Fuso on 04/04/18.
//

#include "token.h"

const char **ids = NULL;
static unsigned int var_count = 0;

char *KEYWORDS[21] =
    {
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
        "fimalgoritmo"
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

char *BOOLEAN_DATA[2] =
    {
        "VERDADEIRO",
        "FALSO"
    };

char *DEL[4] =
    {
        ",",
        ":",
        "(",
        ")",
    };

int
chrcntr(const char *, char);

int
_lookup(const char *);

int
_getid(const char *);

struct Token *
_idtkn(unsigned int, const char *);

struct Line *
_crtln(char *, unsigned int);

struct Token *
_crtkn(TokenType, const char *, unsigned int);

int
is_valid_id(const char *word)
{
    if (!*word)
        return 0;

    if (isalpha(*word))
        word++;
    else
        return 0;

    if (!*word)
        return 1;

    while (*word)
        if (isalnum(*word) == 0)
            return 0;
        else
            word++;
    return 1;
}

int
is_valid_txt(const char *word)
{
    if (!*word)
        return 0;

    while (*word)
        if (*(word) != ' ' && isalnum(*word) == 0)
            return 0;
        else
            word++;
    return 1;
}

int
is_valid_num(const char *word)
{
    if (!*word)
        return 0;

    while (*word)
        if (isdigit(*word) == 0)
            return 0;
        else
            word++;
    return 1;
}

int
chrcntr(const char *haystack, char needle)
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

    line = (struct Line *) malloc(sizeof(struct Line));

    /*
    * body: linha original
    * line_address: número da linha
    * tokens: lista com os tokens gerados nesta linha
    */
    line->body = ln;
    line->line_address = lnum;
    line->tokens = (struct Token **) malloc(LINE_SIZE * sizeof(struct Token *));
    line->error = 0;

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
    struct Token *tmptknstrct = NULL;

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
        if (chrcntr(token, '"') % 2 != 0)
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
        if (tmptknstrct == NULL)
        {
            printf("Comportamento inesperado: L234token.c - encerrando...");
            exit(1);
        }

        if (tmptknstrct->value != NULL)
            lnstrct->tokens[numtkns++] = tmptknstrct;
        else
        {
            lnstrct->error = 1;
            break;
        }
    }

    lnstrct->numtkns = numtkns;

    return lnstrct;
}

int
_lookup(const char *name)
{
    int i;
    for (i = 0; i < var_count; i++)
        if (!strcmp(ids[i], name))
            return i;

    return -1;
}

int
_getid(const char *name)
{
    int x;
    char *cp = NULL;
    cp = (char *) malloc(strlen(name) * sizeof(char) + 1);

    /*
    * Pilha está vazia
    */
    if (!var_count)
    {
        ids = realloc(ids, ++var_count * sizeof(char *) + 1);
        ids[var_count - 1] = strcpy(cp, name);
        return var_count - 1;
    }

    /*
     * Verifica se já existe
     */
    x = _lookup(name);

    if (x != -1)
        return x;

    ids = realloc(ids, ++var_count * sizeof(char *) + 1);
    ids[var_count - 1] = strcpy(cp, name);
    return var_count - 1;
}

struct Token *
_crtkn(TokenType type, const char *body, unsigned int lnum)
{

    struct Token *token = NULL;
    char *tmp = NULL;

    token = (struct Token *) malloc(sizeof(struct Token) + 1);
    tmp = (char *) malloc(sizeof(char) * LINE_SIZE + 1);

    token->raw = body;
    token->tokenType = type;

    switch (type)
    {
        case IDENTIFIER: printf("              ID: %s\n", body);
            snprintf(tmp, LINE_SIZE, "<ID | %d >", _getid(body));
            break;

        case KEYWORD: printf("         Keyword: %s\n", body);
            snprintf(tmp, LINE_SIZE, "<%s>", body);
            break;

        case LOGIC: printf("           LOGIC: %s\n", body);
            snprintf(tmp, LINE_SIZE, "<%s>", body);
            break;

        case NUMBER: printf("          NUMBER: %s\n", body);
            snprintf(tmp, LINE_SIZE, "<NUM | %s >", body);
            break;

        case TEXT: printf("          String: %s\n", body);
            snprintf(tmp, LINE_SIZE, "<STR | \"%s\" >", body);
            break;

        case LOGIC_OPERATOR: printf("  Logic Operator: %s\n", body);
            snprintf(tmp, LINE_SIZE, "<LOP | %s >", body);
            break;

        case OPERATOR: printf("        Operator: %s\n", body);
            snprintf(tmp, LINE_SIZE, "<OP | %s >", body);
            break;

        case DELIMITER: printf("       Delimiter: %s\n", body);
            snprintf(tmp, LINE_SIZE, "<DEL | %s >", body);
            break;

        case UNDEFINED: printf("    Erro de parseamento na linha %d durante a palavra '%s' \n", lnum, body);
            tmp = NULL;
            break;

        default: snprintf(tmp, LINE_SIZE, "<ERROR | %s >", body);
            tmp = NULL;
            break;
    }

    token->value = tmp;

    return token;
}

struct Token *
_idtkn(unsigned int lnum, const char *token)
{
    int i;

    for (i = 0; i < KEYWORDS_SIZE; ++i)
        if (strcmp(token, KEYWORDS[i]) == 0)
            return _crtkn(KEYWORD, token, 0);

    for (i = 0; i < BOOLEAN_DATA_SIZE; ++i)
        if (strcmp(token, BOOLEAN_DATA[i]) == 0)
            return _crtkn(LOGIC, token, 0);

    for (i = 0; i < OP_SIZE; ++i)
        if (strcmp(token, OP[i]) == 0)
            return _crtkn(OPERATOR, token, 0);

    for (i = 0; i < LOGIC_OP_SIZE; ++i)
        if (strcmp(token, LOGIC_OP[i]) == 0)
            return _crtkn(LOGIC_OPERATOR, token, 0);

    for (i = 0; i < DEL_SIZE; ++i)
        if (strcmp(token, DEL[i]) == 0)
            return _crtkn(DELIMITER, token, 0);

    if (!strncmp(token, "\"", 1))
    {
        token++;
        if (is_valid_txt(token))
            return _crtkn(TEXT, token, 0);
        else
            return _crtkn(UNDEFINED, token, lnum);
    }

    if (is_valid_id(token))
        return _crtkn(IDENTIFIER, token, 0);
    else if (is_valid_num(token))
        return _crtkn(NUMBER, token, 0);
    else
        return _crtkn(UNDEFINED, token, lnum);
}

