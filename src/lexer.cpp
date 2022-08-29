#include <vector>
#include <string>
#include <iostream>
#include <token.h>

// i am going to kill you
// make file io now.



void replace_all(std::string& s, std::string const& toReplace, std::string const& replaceWith) {
    std::string buf;
    std::size_t pos = 0;
    std::size_t prevPos;

    // Reserves rough estimate of final size of string.
    buf.reserve(s.size());

    while (true) {
        prevPos = pos;
        pos = s.find(toReplace, pos);
        if (pos == std::string::npos)
            break;
        buf.append(s, prevPos, pos - prevPos);
        buf += replaceWith;
        pos += toReplace.size();
    }

    buf.append(s, prevPos, s.size() - prevPos);
    s.swap(buf);
}

std::vector<std::string> remove_whitespace(std::string string) {
    bool isstr = false;
    std::vector<std::string> out;
    std::string buf;
    for (char currchar : string) {
        if ((currchar == ' ' || currchar == '\n' || currchar == '\r' || currchar == '\t') && !isstr) {
            if (buf.length() != 0) {
                out.push_back(buf);
            }
            
            buf = "";
        } else if (currchar == '\"') {
            isstr = !isstr;
            buf += '\"';
        } else {
            buf += currchar;
        }
    }
    return out;
}

bool isnumber(std::string word) {
    for (char c : word) {
        if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '.') {} else {
            return false;
        }
    }
    return true;
}

bool isfloat(std::string word) {
    for (char c: word) {
        if (c == '.') {
            return true;
        }
    }
    return false;
}

std::vector<Token> tokenise(std::string code) {
    std::string new_code = code;
    replace_all(new_code, "(", " ( ");
    replace_all(new_code, ")", " ) ");
    std::vector<std::string> words = remove_whitespace(new_code);

    std::vector<Token> toRet;
    for (auto word : words) {
        Token tok;
        if (word == "(") {
            tok.m_type = TT_LPAREN;
            tok.m_value = "(";
        } else if (word == ")") {
            tok.m_type = TT_RPAREN;
            tok.m_value = ")";
        } else if (isnumber(word)) {
            if (isfloat(word)) {
                tok.m_type = TT_FLOAT;
            } else {
                tok.m_type = TT_INTEGER;
            }
            tok.m_value = word;
        } else if (word[0] == '\"') {
            tok.m_type = TT_STRING;
            tok.m_value = word;
        } else {
            tok.m_type = TT_SYMBOL;
            tok.m_value = word;
        }
        toRet.push_back(tok);
    }
    return toRet;
}