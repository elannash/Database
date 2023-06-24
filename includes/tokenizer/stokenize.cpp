#include "stokenize.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

StkToken::StkToken() : _token(""), _string_type(TOKEN_UNKNOWN) {}

StkToken::StkToken(string str, int type) : _token(str), _string_type(type) {}

ostream &operator<<(ostream &outs, const StkToken &t)
{
    outs << t._token;
    return outs;
}

int StkToken::string_type() const
{
    return _string_type;
}

string StkToken::type_string() const
{
    if (_string_type == TOKEN_ALPHA)
        return "ALPHA";
    if (_string_type == TOKEN_NUMBER)
        return "NUMBER";
    else if (_string_type == TOKEN_SPACE)
        return "SPACE";
    else if (_string_type == TOKEN_OPERATOR)
        return "OPERATOR";
    else if (_string_type == TOKEN_PUNC)
        return "PUNC";
    else
        return "UNKNOWN";
}

string StkToken::token_str() const
{
    return _token;
}

STokenizer::STokenizer() : _pos(0)
{
    make_table();
}

STokenizer::STokenizer(const char str[]) : _pos(0)
{
    make_table();
    strcpy(_buffer, str);
}

bool STokenizer::done()
{
    return (_pos == strlen(_buffer));
}

bool STokenizer::more()
{
    return !done();
}

STokenizer &operator>>(STokenizer &s, StkToken &token)
{
    string t;          // this is the string that gets passed into get_token() by reference
    int current_state; // this is the current_state that gets passed into get_token(0 by reference)
    int type;          // this is the type that the token is created with

    current_state = 0;
    s.get_token(current_state, t);

    assert(current_state != 0 && "Current state was 0 after calling get_token()");

    // the current_state after get_token() determines the token type
    if (current_state == START_ALPHA)
        type = TOKEN_ALPHA;
    else if (current_state >= START_NUMBER && current_state <= END_NUMBER)
        type = TOKEN_NUMBER;
    else if (current_state == START_SPACE)
        type = TOKEN_SPACE;
    else if (current_state >= START_OPERATOR && current_state <= END_OPERATOR)
        type = TOKEN_OPERATOR;
    else if (current_state == START_PUNC)
        type = TOKEN_PUNC;
    else if (current_state == START_MISC)
        type = TOKEN_MISC;
    else
        type = TOKEN_UNKNOWN;

    token = StkToken(t, type);

    return s;
}

void STokenizer::set_string(const char str[])
{
    _pos = 0; // position should get reset when a new buffer is passed in
    strcpy(_buffer, str);
}

void STokenizer::make_table()
{
    init_table(_table); // initialize table to -1

    // &, |, =, / get their own column to allow for &&, ||, ==, +=, *=, //, etc
    // Currently treating ! as an operator only, not punc (it is not in punc array)
    // Spaces will be appended together and sent back as one token
    // The table:
    // state | success | ALPHA | DIGITS | SPACES | OPERATORS | PUNC | '.' | '&' | '|' | '=' | '/'
    // 0     | 0       | 1     | 2      | 5      | 6         | 12   | 12  | 8   | 10  | 6   | 13
    // 1     | 1       | 1     | -1     | -1     | -1        | -1   | -1  | -1  | -1  | -1  | -1
    // 2     | 1       | -1    | 2      | -1     | -1        | -1   | 3   | -1  | -1  | -1  | -1
    // 3     | 0       | -1    | 4      | -1     | -1        | -1   | -1  | -1  | -1  | -1  | -1
    // 4     | 1       | -1    | 4      | -1     | -1        | -1   | -1  | -1  | -1  | -1  | -1
    // 5     | 1       | -1    | -1     | -1     | -1        | -1   | -1  | -1  | -1  | -1  | -1
    // 6     | 1       | -1    | -1     | -1     | -1        | -1   | -1  | -1  | -1  | 7   | -1
    // 7     | 1       | -1    | -1     | -1     | -1        | -1   | -1  | -1  | -1  | -1  | -1
    // 8     | 1       | -1    | -1     | -1     | -1        | -1   | -1  | 9   | -1  | -1  | -1
    // 9     | 1       | -1    | -1     | -1     | -1        | -1   | -1  | -1  | -1  | -1  | -1
    // 10    | 1       | -1    | -1     | -1     | -1        | -1   | -1  | -1  | 11  | -1  | -1
    // 11    | 1       | -1    | -1     | -1     | -1        | -1   | -1  | -1  | -1  | -1  | -1
    // 12    | 1       | -1    | -1     | -1     | -1        | -1   | -1  | -1  | -1  | -1  | -1
    // 13    | 1       | -1    | -1     | -1     | -1        | -1   | -1  | -1  | -1  | 7   | 14
    // 14    | 1       | -1    | -1     | -1     | -1        | -1   | -1  | -1  | -1  | -1  | -1

    int success_states[] = {1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}; // the rows of the table that are in a success state
    int non_success_states[] = {0, 3};                           // the rows in the table that are not in a success state

    for (int row : success_states)
        mark_success(_table, row);

    for (int row : non_success_states)
        mark_fail(_table, row);

    mark_cells(0, _table, ALPHA, 1);
    mark_cells(0, _table, DIGITS, 2);
    mark_cells(0, _table, SPACES, 5);
    mark_cells(0, _table, OPERATORS, 6);
    mark_cells(0, _table, PUNC, 12);
    mark_cell(0, _table, '&', 8);  // overwrite these operators
    mark_cell(0, _table, '|', 10); // overwrite these operators
    mark_cell(0, _table, '/', 13); // overwrite these operators

    mark_cells(1, _table, ALPHA, 1);

    mark_cells(2, _table, DIGITS, 2);
    mark_cell(2, _table, '.', 3);
    mark_cells(3, _table, DIGITS, 4);
    mark_cells(4, _table, DIGITS, 4);

    mark_cell(6, _table, '=', 7);

    mark_cell(8, _table, '&', 9);

    mark_cell(10, _table, '|', 11);

    mark_cell(0, _table, '/', 13);
    mark_cell(13, _table, '=', 7);
    mark_cell(13, _table, '/', 14);
}

bool STokenizer::get_token(int &current_state, string &token)
{
    int starting_pos;
    int last_success_state;
    int last_success_state_pos;
    unsigned char ch; // unsigned char prevents char overflow caused by extended ascii characters from seg faulting (as they might result in negative index)

    starting_pos = _pos;
    last_success_state = FAIL_STATE;
    last_success_state_pos = FAIL_STATE_POS;
    token = "";

    // while the current state is not in FAIL_STATE and the position index is less than the buffer length
    while (current_state != FAIL_STATE && _pos < strlen(_buffer))
    {
        ch = _buffer[_pos];
        current_state = _table[current_state][ch]; // current_state gets set to the state given by ROW: current_state, COL: buffer[pos] (the character)

        if (_table[current_state][0] == SUCCESS_STATE) // check the success state of the given row
        {
            last_success_state = current_state;
            last_success_state_pos = _pos; // and if success set the last success state position
        }

        _pos++;
    }

    if (last_success_state == FAIL_STATE_POS) // if the last successful state was fail_state, return false
        return false;
    else // the last successful state was not fail_state
    {
        _pos = last_success_state_pos + 1;
        current_state = last_success_state; // this gets set so that we can determine the token type outside of this function

        for (int i = starting_pos; i < _pos; i++)
            token += _buffer[i];

        return true;
    }
}
