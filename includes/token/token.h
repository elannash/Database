#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "_token_constants.h"

using namespace std;

class Token
{
public:
    Token();
    Token(string token_str, int type);

    virtual int type_of() const;

    string get_string() const;
    ostream &print(ostream &outs = cout) const;

    friend ostream &operator<<(ostream &outs, const Token &token);
    friend ostream &operator<<(ostream &outs, const Token *token_ptr);

private:
    int _type;
    string _token_str;
};

//      StkToken();
//      StkToken(string str, int type);
//      friend ostream &operator<<(ostream &outs, const StkToken &t);
//      int string_type() const;
//      string type_string() const;
//      string token_str() const;

//     string _token;
//     int _string_type;

#endif