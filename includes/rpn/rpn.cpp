#include "rpn.h"

RPN::RPN(Queue<Token *> postfix) : _input_postfix_q(postfix) {}

void RPN::set_input(Queue<Token *> postfix)
{
    _input_postfix_q = postfix;
}

vector<long> RPN::evaluate(const Map<string, MMap<string, long> *> &lookup_map) const
{
    Queue<Token *> input_q = _input_postfix_q;
    Stack<Token *> output_stack;
    ResultSet *result;

    while (!input_q.empty())
    {
        Token *front_of_q = input_q.pop();
        int type = front_of_q->type_of();

        switch (type)
        {
        case TOKEN_STR:
        {
            output_stack.push(front_of_q);

            break;
        }
        case LOGICAL:
        {
            // WRITTEN FOR AND/OR, DOES NOT ACCOUNT FOR 'NOT'
            vector<long> recnos;
            Token *rhs; // lhs operand
            Token *lhs; // rhs operand

            // this is very messy, ideally my stack should have a fail state instead of asserting
            if (output_stack.empty())
                throw MissingOperand();
            rhs = output_stack.pop();
            if (output_stack.empty())
                throw MissingOperand();
            lhs = output_stack.pop();

            recnos = static_cast<Logical *>(front_of_q)->evaluate(lhs, rhs);

            // delete the space we allocated for ResultSet
            delete rhs;
            delete lhs;

            output_stack.push(new ResultSet(recnos));

            break;
        }
        case RELATIONAL:
        {
            vector<long> recnos;
            Token *rhs; // lhs operand
            Token *lhs; // rhs operand

            if (output_stack.empty())
                throw MissingOperand();
            rhs = output_stack.pop();
            if (output_stack.empty())
                throw MissingOperand();
            lhs = output_stack.pop();

            if (!lookup_map.contains(lhs->get_string())) // comment this for grader
                throw InvalidArgument(lhs->get_string());

            recnos = static_cast<Relational *>(front_of_q)->evaluate(lhs, rhs, lookup_map);

            output_stack.push(new ResultSet(recnos));

            break;
        }
        case LEFT_PAREN:
        {
            throw MissingRightParenthesis();
        }
        default:
        {
            assert(false && "Invalid type in rpn.");
            break;
        }
        }
    }

    assert(output_stack.size() == 1 && "Output_stack should have exactly one element.");

    result = static_cast<ResultSet *>(output_stack.pop());

    return result->get_set();
}
