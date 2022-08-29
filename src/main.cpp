#include <iostream>
#include <lexer.h>
#include <fstream>
#include <sstream>
#include <parser.h>
#include <token.h>
#include <object.h>

std::string fmt_tokens(std::vector<Token> toks) {
    std::stringstream out;

    for (auto tok: toks) {
        switch (tok.m_type) {
            case TT_INTEGER: {
                out << "INT: " << tok.m_value << '\n';
                break;
            }
            case TT_SYMBOL: {
                out << "SYMBOL: " << tok.m_value << '\n';
                break;
            }
            case TT_LPAREN: {
                out << "LPAREN: (\n";
                break;
            }
            case TT_RPAREN: {
                out << "RPAREN: )\n";
                break;
            }
            case TT_FLOAT: {
                out << "FLOAT: " << tok.m_value << "\n";
                break;
            }
            case TT_STRING: {
                out << "STRING: " << tok.m_value << "\n";
            }
        }
    }
    return out.str();
}

std::string addindentation(int level) {
    std::string indent;
    for (int i = 0; i<level;i++) {
        indent += '\t';
    }
    return indent;
}

std::string fmt_object(std::vector<Object*> ast, int indentation) {
    std::stringstream fmt_out;
    for (int i = 0; i<ast.size();i++) {
        Object* currNode = ast[i];
        switch (currNode->type) {
            case (VOID): {
                fmt_out << addindentation(indentation) <<  "| void\n";
                break;
            }
            case (INTEGER): {
                Integer* intobj = dynamic_cast<Integer*>(currNode);
                fmt_out << addindentation(indentation) << "| int: " << intobj->value << "\n";
                break;
            }
            case (FLOAT): {
                Float* floatobj = dynamic_cast<Float*>(currNode);
                fmt_out << addindentation(indentation) <<"| float: " << floatobj->value << "\n";
                break;
            }
            case (LIST): {
                List* listobj = dynamic_cast<List*>(currNode);
                fmt_out << addindentation(indentation) << "| list:\n" << fmt_object(listobj->value, indentation+1);
                break;
            }
            case (SYMBOL): {
                Symbol* symbolobj = dynamic_cast<Symbol*>(currNode);
                fmt_out << addindentation(indentation) << "| symbol: " << symbolobj->value << '\n';
                break;
            }
            case (STRING): {
                String* stringobj = dynamic_cast<String*>(currNode);
                fmt_out << addindentation(indentation) << "| string: " << stringobj->value << '\n';
                break;
            }
        }

    }
    return fmt_out.str();
}

int main(int argc, char argv[]) {
    //std::ifstream infile ()
    std::vector<Token> toks = tokenise(
        R"V0G0N(
            (
                (define r 10)
                (define pi 3.14)
                (* pi (* r r))
            )
    )V0G0N");
    std::cout << fmt_tokens(toks);
    std::vector<Object*> ast = parse_list(toks, 0).list;
    std::cout << fmt_object(ast, 0);

    /*for (int i = 0;i<ast.size();i++) {
        switch (ast[i]->type) {
            case (SYMBOL): {
                std::cout << "SYMBOL\n";
                break;
            }
            case (INTEGER): {
                std::cout << "INT\n";
                break;
            }
        }
    }*/
    
}