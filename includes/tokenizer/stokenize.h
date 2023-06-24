#ifndef STOKENIZE_H
#define STOKENIZE_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>
#include <string>
#include "constants.h"
#include "statemachinefunctions.h"
#include "../token/token.h"
#include "../token/child_tokens.h"

using namespace std;

/**
 * This StkToken class should be deleted. STokenizer should be able to work with the TokenStr Token child class. 
 * Need to clean up Token class and make sure to avoid vtable errors.
 */
class StkToken
{
public:
    StkToken();
    StkToken(string str, int type);
    friend ostream &operator<<(ostream &outs, const StkToken &t);
    int string_type() const;
    string type_string() const;
    string token_str() const;

private:
    string _token;
    int _string_type;
};

class STokenizer
{
public:
    STokenizer();
    STokenizer(const char str[]);
    bool done(); // true: there are no more tokens
    bool more(); // true: there are more tokens

    friend STokenizer &operator>>(STokenizer &s, StkToken &t);

    // set a new string as the input string
    void set_string(const char str[]);

private:
    // create table for all the tokens we will recognize (e.g. doubles, words, etc.)
    void make_table();

    // extract the longest string that match one of the acceptable token types
    bool get_token(int &current_state, string &token);

    char _buffer[MAX_BUFFER] = {'\0'}; // input string
    int _pos;                          // current position in the string
    static int _table[MAX_ROWS][MAX_COLUMNS];
};

#endif /* STOKENIZE_H */
