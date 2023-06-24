#ifndef RPN_H
#define RPN_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <vector>
#include <exception>

#include "../token/token.h"
#include "../token/child_tokens.h"
#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

using namespace std;

/**
 * @brief Reverse Polish Notation class. Evaluates a postfix expression.
 * @throws MissingOperand, MissingRightParenthesis, InvalidArgument
 */
class RPN
{
public:
    RPN(Queue<Token *> postfix);

    void set_input(Queue<Token *> postfix);
    vector<long> evaluate(const Map<string, MMap<string, long> *> &lookup_map) const;
    vector<long> operator()(const Map<string, MMap<string, long> *> &lookup_map) const { return evaluate(lookup_map); }

private:
    Queue<Token *> _input_postfix_q;
};

// lazy
struct MissingOperand : exception
{
    string error_message;

    MissingOperand()
    {
        error_message = "Missing operand.";
    }

    const char *what() const noexcept
    {
        return error_message.c_str();
    }
};

struct MissingRightParenthesis : exception
{
    string error_message;

    MissingRightParenthesis()
    {
        error_message = "Missing right parenthesis.";
    }

    const char *what() const noexcept
    {
        return error_message.c_str();
    }
};

struct InvalidArgument : exception
{
    string error_message;

    InvalidArgument(string arg)
    {
        error_message = "Argument '" + arg + "' was invalid.";
    }

    const char *what() const noexcept
    {
        return error_message.c_str();
    }
};

#endif