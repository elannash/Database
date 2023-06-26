#include "parser.h"

int Parser::_table[MAX_ROWS][MAX_COLUMNS];

Parser::Parser() : _fail(true) {}

Parser::Parser(string input) : _fail(false)
{
    make_table();
    build_keyword_list();
    set_string(input.c_str());
}

Parser::Parser(const char *input) : _fail(false)
{
    make_table();
    build_keyword_list();
    set_string(input);
}

void Parser::set_string(const char *input)
{
    STokenizer stk(input);
    StkToken token;
    string str;
    int token_type;

    strcpy(_buffer, input); // copy input into internal buffer
    _input_q.clear();       // clear the q before inserting new tokens

    // extract each useful token from the string and push into a queue
    while (stk.more())
    {
        stk >> token;

        str = token.token_str();
        token_type = token.string_type();

        if (token_type != TOKEN_SPACE && str != "\"") // push into the input q if the token isn't a space or quote
            _input_q.push(str);
        else if (stk.more() && str == "\"")
        {
            str = "";

            stk >> token; // throw away the token containing '"'
            while (stk.more() && token.token_str() != "\"")
            {
                str += token.token_str(); // append to the string
                stk >> token;             // get next token
            }

            _input_q.push(str);
        }
    }

    _fail = !get_parse_tree();
}

bool Parser::get_parse_tree()
{
    const bool debug = false;

    int column_no;
    int state = 0;

    _ptree.clear(); // clear the parse tree in case it already contains values

    for (string token : _input_q)
    {
        if (_keywords.contains(token))
            column_no = _keywords[token];
        else
            column_no = SYM;

        state = _table[state][column_no];

        if (state == FAIL_STATE) // if the table returned us a FAIL_STATE, break out of this loop
            break;

        switch (state)
        {
        case 1:
        {
            // MAKE / CREATE BROUGHT US HERE
            // NEXT VALID TOKEN: TABLE
            _ptree["command"] += token;
            break;
        }
        case 2:
        {
            // TABLE BROUGHT US HERE
            // NEXT VALID TOKEN: SYM (table name)
            break;
        }
        case 3:
        {
            // SYM (table name) BROUGHT US HERE
            // NEXT VALID TOKEN: FIELDS
            _ptree["table_name"] += token;
            break;
        }
        case 4:
        {
            // FIELDS / COMMA BROUGHT US HERE
            // NEXT VALID TOKEN: SYM (field name)
            break;
        }
        case 5:
        {
            // SYM (col name) BROUGHT US HERE
            // NEXT VALID TOKEN: COMMA
            _ptree["col"] += token;
            break;
        }
        case 6:
        {
            // INSERT BROUGHT US HERE
            // NEXT VALID TOKEN: INTO
            _ptree["command"] += token;
            break;
        }
        case 7:
        {
            // INTO BROUGHT US HERE
            // NEXT VALID TOKEN: SYM (table name)
            //_ptree["command"] += token; // to add "into" to _ptree["commands"]
            break;
        }
        case 8:
        {
            // SYM (table name) BROUGHT US HERE
            // NEXT VALID TOKEN: VALUES
            _ptree["table_name"] += token;
            break;
        }
        case 9:
        {
            // VALUES / COMMA BROUGHT US HERE
            // NEXT VALID TOKEN: SYM (value)
            break;
        }
        case 10:
        {
            // SYM (value) BROUGHT US HERE
            // NEXT VALID TOKEN: COMMA
            _ptree["values"] += token;
            break;
        }
        case 11:
        {
            // SELECT BROUGHT US HERE
            // NEXT VALID TOKEN: STAR, SYM (field)
            _ptree["command"] += token;
            break;
        }
        case 12:
        {
            // STAR (field) BROUGHT US HERE
            // NEXT VALID TOKEN: FROM
            _ptree["fields"] += token;
            break;
        }
        case 13:
        {
            // SYM (field) BROUGHT US HERE
            // NEXT VALID TOKEN: FROM, COMMA
            _ptree["fields"] += token;
            break;
        }
        case 14:
        {
            // FROM BROUGHT US HERE
            // NEXT VALID TOKEN: SYM (table name)
            break;
        }
        case 15:
        {
            // SYM (table name) BROUGHT US HERE
            // NEXT VALID TOKEN: WHERE
            _ptree["table_name"] += token;
            break;
        }
        case 16:
        {
            // COMMA BROUGHT US HERE
            // NEXT VALID TOKEN: SYM (field)
            break;
        }
        case 17:
        {
            // WHERE BROUGHT US HERE
            // NEXT VALID TOKEN: SYM (condition)
            _ptree["where"] += string("yes");
            break;
        }
        case 18:
        {
            // SYM (condition) BROUGHT US HERE
            // NEXT VALID TOKEN: AND, OR, SYM (condition)
            _ptree["condition"] += token;
            break;
        }
        case 19:
        {
            // AND / SYM (condition) BROUGHT US HERE
            // NEXT VALID TOKEN: SYM (condition)
            _ptree["condition"] += token;
            break;
        }
        case 20:
        {
            // SYM (condition) BROUGHT US HERE
            // NEXT VALID TOKEN: AND, OR, SYM (condition)
            _ptree["condition"] += token;
            break;
        }
        case 21:
        {
            // OR (condition) BROUGHT US HERE
            // NEXT VALID TOKEN: SYM (condition)
            _ptree["condition"] += token;
            break;
        }
        }
    }

    if (_table[state][0] == SUCCESS_STATE)
        return true;
    else
    {
        if (debug)
            cout << "In get_parse_tree(): Failed to parse. Last state was " << state << "." << endl;

        _ptree.clear();

        return false;
    }
}

bool Parser::fail()
{
    return _fail;
}

MMap<string, string> Parser::parse_tree()
{
    return _ptree;
}

void Parser::build_keyword_list()
{
    // map keywords to their column in the adjacency matrix

    string keyword_strings[] = {"make", "create", "table", "insert", "into", "values", "select", "from", "fields", "*", "where", "and", "or", ","};
    int enum_value;

    enum_value = 1;                        // value starts from one in accordance with declared enum (we are not mapping ZERO)
    for (string keyword : keyword_strings) // for each string in keyword_strings, map to the appropriate enum value
    {
        _keywords.insert(keyword, enum_value);
        ++enum_value;
    }
}

/**
 * @brief Builds the adjacency matrix for keywords.
 *
 */
void Parser::make_table()
{
    // can implement:
    // INSERT SYM -> same as insert into, just change SYM in row ? to ?
    // INSERT INTO tablename columns -> insert values into specific columns
    // ALTER to change the columns of the table
    // UPDATE to update info already inserted into the table

    // the table:
    // state | success | MAKE | CREATE | TABLE | INSERT | INTO | VALUES | SELECT | FROM | FIELDS | STAR | WHERE | AND | OR | COMMA | SYM
    // 0     | 0         1      1        -1      6        -1     -1       11       -1     -1       -1     -1      -1    -1   -1      -1
    // 1     | 0         -1     -1       2       -1       -1     -1       -1       -1     -1       -1     -1      -1    -1   -1      -1
    // 2     | 0         -1     -1       -1      -1       -1     -1       -1       -1     -1       -1     -1      -1    -1   -1      3
    // 3     | 0         -1     -1       -1      -1       -1     -1       -1       -1     4        -1     -1      -1    -1   -1      -1
    // 4     | 0         -1     -1       -1      -1       -1     -1       -1       -1     -1       -1     -1      -1    -1   -1       5
    // 5     | 1         -1     -1       -1      -1       -1     -1       -1       -1     -1       -1     -1      -1    -1   4       -1
    // 6     | 0         -1     -1       -1      -1       7      -1       -1       -1     -1       -1     -1      -1    -1   -1      -1
    // 7     | 0         -1     -1       -1      -1       -1     -1       -1       -1     -1       -1     -1      -1    -1   -1      8
    // 8     | 0         -1     -1       -1      -1       -1     9        -1       -1     -1       -1     -1      -1    -1   -1      -1
    // 9     | 0         -1     -1       -1      -1       -1     -1       -1       -1     -1       -1     -1      -1    -1   -1      10
    // 10    | 1         -1     -1       -1      -1       -1     -1       -1       -1     -1       -1     -1      -1    -1   9       -1
    // 11    | 0         -1     -1       -1      -1       -1     -1       -1       -1     -1       12     -1      -1    -1   -1      13
    // 12    | 0         -1     -1       -1      -1       -1     -1       -1       14     -1       -1     -1      -1    -1   -1      -1
    // 13    | 0         -1     -1       -1      -1       -1     -1       -1       14     -1       -1     -1      -1    -1   16      -1
    // 14    | 0         -1     -1       -1      -1       -1     -1       -1       -1     -1       -1     -1      -1    -1   -1      15
    // 15    | 1         -1     -1       -1      -1       -1     -1       -1       -1     -1       -1     17      -1    -1   -1      -1
    // 16    | 0         -1     -1       -1      -1       -1     -1       -1       -1     -1       -1     -1      -1    -1   -1      13
    // 17    | 0         -1     -1       -1      -1       -1     -1       -1       -1     -1       -1     -1      -1    -1   -1      18
    // 18    | 1         -1     -1       -1      -1       -1     -1       -1       -1     -1       -1     -1      19    21   -1      18
    // 19    | 0         -1     -1       -1      -1       -1     -1       -1       -1     -1       -1     -1      -1    -1   -1      20
    // 20    | 1         -1     -1       -1      -1       -1     -1       -1       -1     -1       -1     -1      19    21   -1      20
    // 21    | 0         -1     -1       -1      -1       -1     -1       -1       -1     -1       -1     -1      -1    -1   -1      19

    init_table(_table); // initialize the table to -1

    int success_states[] = {5, 10, 15, 18, 20};                                             // the rows of the table that are in a success state
    int non_success_states[] = {0, 1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 16, 17, 19, 21}; // the rows in the table that are not in a success state

    for (int row : success_states)
        mark_success(_table, row);

    for (int row : non_success_states)
        mark_fail(_table, row);

    mark_cell(0, _table, MAKE, 1);
    mark_cell(0, _table, CREATE, 1);
    mark_cell(0, _table, INSERT, 6);
    mark_cell(0, _table, SELECT, 11);
    mark_cell(1, _table, TABLE, 2);
    mark_cell(2, _table, SYM, 3);
    mark_cell(3, _table, FIELDS, 4);
    mark_cell(4, _table, SYM, 5);
    mark_cell(5, _table, COMMA, 4);
    mark_cell(6, _table, INTO, 7);
    // mark_cell(6, _table, SYM, 8);
    mark_cell(7, _table, SYM, 8);
    mark_cell(8, _table, VALUES, 9);
    mark_cell(9, _table, SYM, 10);
    mark_cell(10, _table, COMMA, 9);
    mark_cell(11, _table, STAR, 12);
    mark_cell(11, _table, SYM, 13);
    mark_cell(12, _table, FROM, 14);
    mark_cell(13, _table, FROM, 14);
    mark_cell(13, _table, COMMA, 16);
    mark_cell(14, _table, SYM, 15);
    mark_cell(15, _table, WHERE, 17);
    mark_cell(16, _table, SYM, 13);
    mark_cell(17, _table, SYM, 18);
    mark_cell(18, _table, AND, 19);
    mark_cell(18, _table, OR, 21);
    mark_cell(18, _table, SYM, 18);
    mark_cell(19, _table, SYM, 20);
    mark_cell(20, _table, AND, 19);
    mark_cell(20, _table, OR, 21);
    mark_cell(20, _table, SYM, 20);
    mark_cell(21, _table, SYM, 19);

    // print_table(_table, 0, SYM, 21);
}