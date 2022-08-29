#ifndef PARSER_H
#define PARSER_H
#include <object.h>
#include <token.h>
#include <vector>

struct ParseReturnType {
    std::vector<Object*> list;
    int idx;
};

ParseReturnType parse_list(std::vector<Token> toks, int idx);
#endif