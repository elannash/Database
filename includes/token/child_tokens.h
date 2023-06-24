#ifndef CHILD_TOKENS_H
#define CHILD_TOKENS_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include "token.h"

using namespace std; 

class TokenStr : public Token
{
public:
    TokenStr(string token_str);

    int type_of() const;
    string token_str() const;

private:
};

class Operator : public Token
{
public:
    Operator(string token_str);

    // returns pointer to object containing vector
    virtual int get_prec() const;
    virtual int type_of() const;

    string get_op() const;

private:
    string _operator;
};

class LeftParen : public Token
{
public:
    LeftParen();

    int type_of() const;

    virtual ostream &print(ostream &outs = cout) const;
};

class RightParen : public Token
{
public:
    RightParen();

    int type_of() const;
    
    virtual ostream &print(ostream &outs = cout) const;
};

class Logical : public Operator
{
public:
    Logical(string token_str);

    vector<long> evaluate(Token *lhs, Token *rhs) const;
    int get_prec() const;
    int type_of() const;

private:
    int _precedence;
};

class Relational : public Operator
{
public:
    Relational(string token_str);

    vector<long> evaluate(Token *lhs, Token *rhs, const Map<string, MMap<string, long> *> &lookup_map) const;
    int get_prec() const;
    int type_of() const;

private:
    int _precedence;
};

class ResultSet : public Token
{
public:
    ResultSet(const vector<long> &recnos);

    vector<long> get_set();
    int type_of() const;

private:
    vector<long> _recnos;
};

#endif /* CHILD_TOKENS_H */
