#ifndef SQL_H
#define SQL_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <cassert>
#include <exception>

#include "../table/table.h"
#include "../parser/parser.h"
#include "../tokenizer/ftokenize.h"
#include "../bplustree/multimap.h"
#include "../stl_utils/vector_utilities.h"

using namespace std;

/**
 * @brief Manages a database of tables using SQL-like commands.
 * @throws InvalidCommand, InvalidField, TooManyValues
 */
class SQL
{
public:
    SQL();
    SQL(const char *file_name);
    ~SQL();

    Table command(string command);
    void batch_mode(const char *file_name);

    vector<long> select_recnos() const { return _table.select_recnos(); }
    Table get_table() const { return _table; }

private:
    Table _table;
    Parser _parser;
    MMap<string, string> _ptree;

    Table make_table();
    Table insert_into_table();
    Table select_from_table();
};

// user entered a command that failed to parse
struct InvalidCommand : exception
{
    string error_message;

    InvalidCommand(string command)
    {
        error_message = "Command '" + command + "' was invalid.";
    }

    const char *what() const noexcept
    {
        return error_message.c_str();
    }
};

// when user inserts too many values into the table
struct TooManyValues : exception
{
    string error_message;

    TooManyValues(string last_valid_element)
    {
        error_message = "Values past '" + last_valid_element + "' exceed the number of table columns.";
    }

    const char *what() const noexcept
    {
        return error_message.c_str();
    }
};

#endif /* SQL_H */
