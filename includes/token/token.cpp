#include "token.h"

Token::Token() : _token_str("UNINITIALIZED"), _type(TOKEN_UNKNOWN) {}

Token::Token(string token_str, int type) : _token_str(token_str), _type(type) {}

int Token::type_of() const
{
    return _type;
}

string Token::get_string() const
{
    return _token_str;
}

ostream &Token::print(ostream &outs) const
{
    outs << _token_str;
    return outs;
}

ostream &operator<<(ostream &outs, const Token &token)
{
    token.print(outs);
    return outs;
}

ostream &operator<<(ostream &outs, const Token *token_ptr)
{
    token_ptr->print(outs);
    return outs;
}