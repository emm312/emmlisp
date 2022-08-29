#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <vector>

enum ObjectTypes {
    VOID,
    INTEGER,
    FLOAT,
    STRING,
    BOOL,
    SYMBOL,
    LAMBDA,
    LIST
};


class Object {public: virtual ~Object(){} ObjectTypes type; };

struct Void : Object {};
struct Integer : Object { int value; };
struct Float : Object { float value; };
struct String : Object { std::string value; };
struct Bool : Object { bool value; };
struct Symbol : Object { std::string value; };
struct Lambda : Object { std::vector<std::string> name; std::vector<Object*> contents;};
struct List : Object { std::vector<Object*> value; };

#endif