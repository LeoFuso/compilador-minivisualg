//
// Created by Leonardo Fuso on 01/04/18.
//

#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
    IDENTIFIER,
    KEYWORD,
    NUMBER,
    TEXT,
    LOGIC_OPERATOR,
    OPERATOR,
    DELIMITER,
    UNDEFINED,
    EOT
} TokenType;

struct Token
{
    TokenType tokenType;
    char *value;
};

struct Line
{
    int line_address;
    char *body;
    Token *tokens;
};

#endif //TOKEN_H
