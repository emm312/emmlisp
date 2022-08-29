#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum TokenTypes {
    TT_LPAREN,
    TT_RPAREN,
    TT_INTEGER,
    TT_SYMBOL,
    TT_FLOAT,
    TT_STRING
};

struct Token {
    std::string m_value;
    TokenTypes m_type;
};


#endif