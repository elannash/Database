#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cassert>
#include "../bplustree/multimap.h"
#include "../tokenizer/stokenize.h"
#include "../queue/MyQueue.h"
#include "../stl_utils/vector_utilities.h"
#include "../table/typedefs.h"

using namespace std;

enum Keywords
{
    ZERO, // need this to avoid writing in first column of adjacency matrix
    MAKE,
    CREATE,
    TABLE,
    INSERT,
    INTO,
    VALUES,
    SELECT,
    FROM,
    FIELDS,
    STAR,
    WHERE,
    AND,
    OR,
    COMMA,
    SYM
    // ALTER
    // DROP
    // DELETE
};

class Parser
{
public:
    Parser(); // fail will be initialized to true for default ctor
    Parser(string input);
    Parser(const char *input);

    void set_string(const char *input);

    bool fail();
    MMap<string, string> parse_tree();

private:
    bool _fail;
    char _buffer[MAX_BUFFER]; // not using currently

    Queue<string> _input_q;
    MMap<string, string> _ptree;
    Map<string, int> _keywords;

    // void get_column();
    bool get_parse_tree();

    void build_keyword_list();
    void make_table();

    static int _table[MAX_ROWS][MAX_COLUMNS];
};

#endif /* PARSER_H */

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