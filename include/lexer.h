#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include <string>
#include <token.h>
std::vector<Token> tokenise(std::string code);
#endif