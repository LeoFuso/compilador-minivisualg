//
// Created by Leonardo Fuso on 01/04/18.
//

#ifndef TOKEN_H
#define TOKEN_H


typedef enum {
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


typedef struct {
    TokenType tokenType;
    char *value;
    int line_address;
};


#endif //TOKEN_H
