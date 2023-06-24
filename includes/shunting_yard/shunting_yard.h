#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <exception>

#include "../token/token.h"
#include "../token/child_tokens.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

using namespace std;

/**
 * @brief Shunting yard algorithm for conditions.
 * @throws MissingLeftParenthesis
 */
class ShuntingYard
{
public:
    ShuntingYard(const Queue<Token *> &infix);

    Queue<Token *> postfix();

private:
    Queue<Token *> _infix_q;
};

// lazy
struct MissingLeftParenthesis : exception
{
    string error_message;

    MissingLeftParenthesis()
    {
        error_message = "Missing left parenthesis.";
    }

    const char *what() const noexcept
    {
        return error_message.c_str();
    }
};

#endif