#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <object.h>
#include <map>

struct Env {
    Env* parent;
    std::map<std::string, Object*> vars;
};


Object* eval_obj(Object* obj, Env env);

#endif