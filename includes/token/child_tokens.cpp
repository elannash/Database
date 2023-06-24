#include "child_tokens.h"

TokenStr::TokenStr(string token_str) : Token(token_str, TOKEN_STR) {}

int TokenStr::type_of() const
{
    return TOKEN_STR;
}

string TokenStr::token_str() const
{
    return Token::get_string();
}

Operator::Operator(string token_str) : Token(token_str, OPERATOR), _operator(token_str) {}

int Operator::type_of() const
{
    return OPERATOR;
}

int Operator::get_prec() const
{
    return UNKNOWN_PREC;
}

string Operator::get_op() const
{
    return _operator;
}

LeftParen::LeftParen() : Token("(", LEFT_PAREN) {}

int LeftParen::type_of() const
{
    return LEFT_PAREN;
}

ostream &LeftParen::print(ostream &outs) const
{
    outs << "(";
    return outs;
}

RightParen::RightParen() : Token(")", RIGHT_PAREN) {}

int RightParen::type_of() const
{
    return RIGHT_PAREN;
}

ostream &RightParen::print(ostream &outs) const
{
    outs << ")";
    return outs;
}

Logical::Logical(string token_str) : Operator(token_str)
{
    // AND takes precedence over OR
    // if NOT was implemented, it would take precedence over AND
    if (token_str == "not")
        _precedence = LOGICAL_NOT_PREC;
    else if (token_str == "and")
        _precedence = LOGICAL_AND_PREC;
    else
        _precedence = LOGICAL_OR_PREC;
}

vector<long> Logical::evaluate(Token *lhs, Token *rhs) const
{
    vector<long> left;
    vector<long> right;
    vector<long> result;

    left = static_cast<ResultSet *>(lhs)->get_set();
    right = static_cast<ResultSet *>(rhs)->get_set();

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    if (Operator::get_op() == "and")
        set_intersection(left.begin(), left.end(), right.begin(), right.end(), back_inserter(result));
    else if (Operator::get_op() == "or")
        set_union(left.begin(), left.end(), right.begin(), right.end(), back_inserter(result));
    else
        assert(false && "Logical operator was invalid.");

    return result;
}

int Logical::get_prec() const
{
    return _precedence;
}

int Logical::type_of() const
{
    return LOGICAL;
}

Relational::Relational(string token_str) : Operator(token_str), _precedence(RELATIONAL_PREC) {}

vector<long> Relational::evaluate(Token *lhs, Token *rhs, const Map<string, MMap<string, long> *> &lookup_map) const
{
    assert(lookup_map.contains(lhs->get_string()) && "Lookup map did not contain argument when calling evaluate.");

    vector<long> recnos;
    MMap<string, long>::Iterator it;
    string left = lhs->get_string();
    string right = rhs->get_string();

    // if (!lookup_map.contains(left)) // delete this, uncomment assert above
    //     return recnos;

    if (Operator::get_op() == "=")
    {
        // need to check if the map contains right before accessing it via [] operator so I do not add it to the bptree when calling []
        if (!(*lookup_map[left]).contains(right))
            return recnos;

        // return the vector at (*lookup_map[left])[right]
        recnos = (*lookup_map[left])[right];
    }
    else if (Operator::get_op() == ">=")
    {
        // iterate from lower bound to end
        for (it = (*lookup_map[left]).lower_bound(right); it != (*lookup_map[left]).end(); it++)
            recnos += (*it).value_list;
    }
    else if (Operator::get_op() == "<=")
    {
        // iterate from begin to upper bound
        for (it = (*lookup_map[left]).begin(); it != (*lookup_map[left]).upper_bound(right); it++)
            recnos += (*it).value_list;
    }
    else if (Operator::get_op() == ">")
    {
        // iterate from upper bound to end
        for (it = (*lookup_map[left]).upper_bound(right); it != (*lookup_map[left]).end(); it++)
            recnos += (*it).value_list;
    }
    else if (Operator::get_op() == "<")
    {
        // iterate from begin to lower bound
        for (it = (*lookup_map[left]).begin(); it != (*lookup_map[left]).lower_bound(right); it++)
            recnos += (*it).value_list;
    }
    else
        assert(false && "Relational operator was invalid.");

    return recnos;
}

int Relational::get_prec() const
{
    return _precedence;
}

int Relational::type_of() const
{
    return RELATIONAL;
}

ResultSet::ResultSet(const vector<long> &recnos) : Token("", RESULT_SET), _recnos(recnos) {}

vector<long> ResultSet::get_set()
{
    return _recnos;
}

int ResultSet::type_of() const
{
    return RESULT_SET;
}