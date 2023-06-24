#include "shunting_yard.h"

ShuntingYard::ShuntingYard(const Queue<Token *> &infix) : _infix_q(infix) {}

Queue<Token *> ShuntingYard::postfix()
{
    Queue<Token *> postfix_q;
    Stack<Token *> holding_stack;

    while (!_infix_q.empty())
    {
        Token *front_of_q = _infix_q.pop();
        int type = front_of_q->type_of(); // store the Token type of the token at the front of the queue in a local variable

        switch (type)
        {
        case TOKEN_STR:
        {
            postfix_q.push(front_of_q);

            break;
        }
        case LOGICAL:
        case RELATIONAL:
        {
            if (!holding_stack.empty())
            {
                Token *top_of_stack = holding_stack.top();

                if (top_of_stack->type_of() == LEFT_PAREN)
                    holding_stack.push(front_of_q);
                else if (static_cast<Operator *>(top_of_stack)->get_prec() < static_cast<Operator *>(front_of_q)->get_prec())
                    holding_stack.push(front_of_q);
                else // precedence of operator at the top of the stack is greater or equal to the precedence of the operator at front of queue
                {
                    // while the holding stack is not empty and not a parenthesis, and the item at the top of the stack has a lower precedence than the item at the front of the queue
                    // pop the stack and push whatever was on top into the postfix queue
                    // we also need to check if the token at the top of the stack is a left_paren to avoid calling get_prec() on it

                    while ((!holding_stack.empty() && (holding_stack.top()->type_of() != LEFT_PAREN)) && (static_cast<Operator *>(holding_stack.top())->get_prec() >= static_cast<Operator *>(front_of_q)->get_prec()))
                        postfix_q.push(holding_stack.pop());

                    holding_stack.push(front_of_q);
                }
            }
            else
                holding_stack.push(front_of_q);

            break;
        }
        case LEFT_PAREN:
        {
            holding_stack.push(front_of_q);

            break;
        }
        case RIGHT_PAREN:
        {
            Token *delete_me;

            // pop the stack until we find the matching left parenthesis
            while (holding_stack.top()->type_of() != LEFT_PAREN)
            {
                postfix_q.push(holding_stack.pop());

                if (holding_stack.empty())
                    throw MissingLeftParenthesis();
            }

            // pop the left parenthesis
            delete_me = holding_stack.pop();

            // release memory for left and rightparen here
            delete delete_me;
            delete front_of_q;

            break;
        }
        default:
        {
            assert(false && "Invalid type in shunting yard.");
            break;
        }
        }
    }

    while (!holding_stack.empty())
        postfix_q.push(holding_stack.pop());

    return postfix_q;
}