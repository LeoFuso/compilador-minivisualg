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

char *OPERATORS[7] =
    {
        "+",
        "-",
        "*",
        "/",
        "mod",
        "exp",
        "<-"
    };

char *LOGIC_OPERATORS[8] =
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

char *BOOLEAN_OPERATORS[2] =
    {
        "verdadeiro",
        "falso"
    };

char *DELIMITERS[4] =
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

struct Token *
_new_tkn(struct Token *);

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
     * body: original line
     * line_address: line number
     * tokens: list with generated tokens in this line
     */
    line->body = ln;
    line->line_address = lnum;
    line->tokens = (struct Token **) malloc(LINE_SIZE * 2 * sizeof(struct Token *));
    line->error = 0;

    return line;
}

struct Line *
_strbldr(unsigned int lnum, char *line)
{
    /*
     *  Space Delimiters
     */
    char *dlim_spc = " ";
    char *dlim_str = "\"";
    char *dlim = dlim_spc;

    /*
     * Token in string form
     */
    char *token;

    /*
     * struct Line to be later used in parsing
     */
    struct Line *lnstrct = NULL;
    struct Token *tmptknstrct = NULL;

    unsigned int numtkns;

    lnstrct = _crtln(line, lnum);
    numtkns = 0;

    /*
     * A repeating structure that traverses the cut-out chunks of the string
     * using the space delimiters as a parameter
     */
    for (token = strtok(line, dlim); token != NULL; token = strtok(NULL, dlim))
    {
        /*
         * Checks if open comment is closed
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
         * Checking comments on line:
         * Everything after the '//' is ignored
         */
        if (!strncmp(token, "//", 2))
            break;

        /*
         * Attempts to create a token from the trimmed piece of string
         */
        tmptknstrct = _idtkn(lnum, token);

        /*
         * If successful, insert a new token in the token list
         */
        if (tmptknstrct == NULL)
        {
            printf("Unexpected behavior: token.c 187 - closing ...");
            exit(1);
        }

        if (tmptknstrct->body != NULL)
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
     *  Stack is empty
     */
    if (!var_count)
    {
        ids = realloc(ids, ++var_count * sizeof(char *) + 1);
        ids[var_count - 1] = strcpy(cp, name);
        return var_count - 1;
    }

    /*
     * Check if it already exists
     */
    x = _lookup(name);

    if (x != -1)
        return x;

    ids = realloc(ids, ++var_count * sizeof(char *) + 1);
    ids[var_count - 1] = strcpy(cp, name);
    return var_count - 1;
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

struct Token *
_crtkn(TokenType type, const char *body, unsigned int lnum)
{

    struct Token *token = NULL;
    char *tmp_body = NULL;
    char *tmp_value = NULL;

    token = _new_tkn(token);
    tmp_body = (char *) malloc(sizeof(char) * LINE_SIZE + 1);
    tmp_value = (char *) malloc(sizeof(char) * LINE_SIZE + 1);

    token->tokenType = type;
    token->source = body;

    switch (type)
    {
        case IDENTIFIER: printf("              ID: %s\n", body);
            sprintf(tmp_value, "%d", _getid(body));
            snprintf(tmp_body, LINE_SIZE, "<id | %s >", tmp_value);
            break;

        case KEYWORD: printf("         Keyword: %s\n", body);
            strcpy(tmp_value, body);
            snprintf(tmp_body, LINE_SIZE, "<%s>", body);
            break;

        case BOOLEAN_OPERATOR: printf("Boolean Operator: %s\n", body);
            strcpy(tmp_value, body);
            snprintf(tmp_body, LINE_SIZE, "<%s>", body);
            break;

        case NUMBER: printf("          Number: %s\n", body);
            strcpy(tmp_value, body);
            snprintf(tmp_body, LINE_SIZE, "<num | %s >", body);
            break;

        case TEXT: printf("          String: %s\n", body);
            strcpy(tmp_value, body);
            snprintf(tmp_body, LINE_SIZE, "<str | \"%s\" >", body);
            break;

        case LOGIC_OPERATOR: printf("  Logic Operator: %s\n", body);
            strcpy(tmp_value, body);
            snprintf(tmp_body, LINE_SIZE, "<lop | %s >", body);
            break;

        case OPERATOR: printf("        Operator: %s\n", body);
            strcpy(tmp_value, body);
            snprintf(tmp_body, LINE_SIZE, "<op | %s >", body);
            break;

        case DELIMITER: printf("       Delimiter: %s\n", body);
            strcpy(tmp_value, body);
            snprintf(tmp_body, LINE_SIZE, "<del | %s >", body);
            break;

        case UNDEFINED: printf("                   Parse error on line %d during word '%s' \n", lnum, body);
            tmp_value = NULL;
            tmp_body = NULL;
            break;

        default: snprintf(tmp_body, LINE_SIZE, "<ERROR | %s >", body);
            tmp_value = NULL;
            tmp_body = NULL;
            break;
    }

    token->value =  tmp_value;
    token->body = tmp_body;

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
        if (strcmp(token, BOOLEAN_OPERATORS[i]) == 0)
            return _crtkn(BOOLEAN_OPERATOR, token, 0);

    for (i = 0; i < OP_SIZE; ++i)
        if (strcmp(token, OPERATORS[i]) == 0)
            return _crtkn(OPERATOR, token, 0);

    for (i = 0; i < LOGIC_OP_SIZE; ++i)
        if (strcmp(token, LOGIC_OPERATORS[i]) == 0)
            return _crtkn(LOGIC_OPERATOR, token, 0);

    for (i = 0; i < DEL_SIZE; ++i)
        if (strcmp(token, DELIMITERS[i]) == 0)
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

struct Token *
_new_tkn(struct Token *token)
{
    token = (struct Token *) malloc(sizeof(struct Token) + 1);

    token->value = (char *) malloc(sizeof(char) * LINE_SIZE + 1);
    token->body = (char *) malloc(sizeof(char) * LINE_SIZE + 1);
    token->source = (char *) malloc(sizeof(char) * LINE_SIZE + 1);
    return token;
}

