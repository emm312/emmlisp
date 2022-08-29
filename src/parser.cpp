#include <iostream>
#include <vector>
#include <token.h>
#include <string>
#include <object.h>
#include <parser.h>

ParseReturnType parse_list(std::vector<Token> toks, int idx) {
    std::vector<Object*> toRet;
    if (toks[idx].m_type != TT_LPAREN) {
        std::cerr << "ERROR: Expected (, found \"" << toks[idx].m_value << "\"\n";
        exit(-1);
    }
    for (int i = idx+1; i< toks.size(); i++) {
        switch (toks[i].m_type) {
            case TT_INTEGER: {
                Integer *node = new Integer();
                node->type = INTEGER;
                node->value = std::stoi(toks[i].m_value);
                toRet.push_back(node);
                break;
            }
            case TT_SYMBOL: {
                Symbol *node = new Symbol();
                node->type = SYMBOL;
                node->value = toks[i].m_value;
                toRet.push_back(node);
                break;
            }
            case TT_LPAREN: {
                List *node = new List();
                node->type = LIST;
                ParseReturnType innerlist = parse_list(toks, i);
                node->value = innerlist.list;
                i = innerlist.idx;
                toRet.push_back(node);
                break;
            }
            case TT_FLOAT: {
                Float *node = new Float();
                node->type = FLOAT;
                node->value = std::stof(toks[i].m_value);
                toRet.push_back(node);
                break;
            }
            case TT_STRING: {
                String *node = new String();
                node->type = STRING;
                node->value = toks[i].m_value;
                toRet.push_back(node);
                break;
            }
            case TT_RPAREN: {
                ParseReturnType ret;
                ret.list = toRet;
                ret.idx = i;
                return ret;
                break;
            }
        }
    }
    std::cerr << "Invalid syntax.\n";
    exit(-1);
}

// go check below
/*
struct Base
{
	int val;
}

struct Derived1: Base
{
	int val1;
}

struct Derived2: Base
{
	int val2;
}

Base val = Derived1();
Derived2 val2 = (Derived2) val;
// 'val' is of type Base, and Derived2 is a subclass of Base, so this cast is technically valid
// but the actual data at val is of typed Derived1, so this cast will return data to garbage now
// you can still use val2 but its undefined behaviour (segfault or weird values)
// you can't check if its valid with an if because it returns data to what you now think is of type
// Derived2

Base* val3 = new Derived1();
Derived2* val4 = dynamic_cast<Derived2*>(val3);
// val4 is a nullptr because dynamic_cast returns nullptr when types dont match
// and you can easily check for nullptr with if

*/
