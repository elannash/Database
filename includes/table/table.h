#ifndef TABLE_H
#define TABLE_H

#include <algorithm>
#include <exception>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>

#include "../avl/avl.h"
#include "../binary_files/file_record.h"
#include "../bplustree/multimap.h"
#include "../bplustree/map.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"
#include "../token/token.h"
#include "../token/child_tokens.h"
#include "typedefs.h"

/**
 * @brief Class that manages a single table. Has functions to open other tables, and select values adhering to certain conditions.
 * @throws TableAlreadyExists, InvalidTable, InvalidField
 */
class Table
{
public:
    Table();
    Table(string table_name);                                    // opens existing file
    Table(string table_name, const vector<string> &field_names); // creates a file with field names

    Table(const Table &other);
    ~Table();

    Table operator=(const Table &rhs);

    vector<string> get_fields() const; // return vector of field names

    void insert_into(vector<string> field_values);

    Table select_all();
    Table select(const vector<string> &field_names);
    Table select(const vector<string> &field_names, string field, string op, string value);
    Table select(const vector<string> &field_names, const Queue<Token *> &postfix);
    Table select(const vector<string> &field_names, const vector<string> &infix_strings);

    vector<long> select_recnos() const;

    string get_table_name() const { return _table_name; }
    bool empty() const { return _total_records == 0; }
    Map<string, long> get_field_names_column_indices() { return _field_names_column_indices; }
    AVL<string> get_field_names_tree() { return _field_names_tree; } // useful when searching for field name, probably unnecessary
    string get_bin_file_name() { return _bin_file_name; }
    string get_txt_file_name() { return _txt_file_name; }

    // i should make a pretty print function/class that uses nice unicode characters
    friend ostream &operator<<(ostream &outs, const Table &print_me)
    {
        fstream f;
        FileRecord r;
        int recno;
        long bytes;

        open_fileRW(f, print_me._bin_file_name.c_str());

        outs << "Table name: " << print_me._table_name << ", records: " << print_me._total_records << endl;
        outs << setw(25) << "record";
        for (string field_name : print_me._field_names)
            outs << setw(25) << field_name;
        outs << endl
             << endl;

        recno = 0;
        bytes = r.read(f, recno);
        while (bytes > 0)
        {
            outs << setw(25) << recno << r << endl;
            recno++;
            bytes = r.read(f, recno);
        }

        return outs;
    }

private:
    static long _serial; // table serial number, incremented every time a new table is created

    string _table_name;
    string _bin_file_name; // no good reason why i'm storing both of these file names other than easy deletion
    string _txt_file_name;
    // char _file_name[255];

    long _total_records;
    vector<long> _last_selected_recnos;

    void copy_table(const Table &rhs); // objects will still share a file after copying. not good! (if the table is a _select table, the destructor will remove its file)
    void clear_table();
    void set_fields(const vector<string> &field_names); // set vector of field names

    void reindex();

    vector<long> cond(const Queue<Token *> &postfix) const;  // returns a vector of recnos that adhere to condition
    Table vector_to_table(const vector<long> &recnos) const; // takes a vector of record numbers and returns a table
    Table vector_to_table(const vector<string> &field_names, const vector<long> &recnos) const;

    Queue<Token *> tokenize(const vector<string> &infix_strings) const; // take vector of infix strings and return vector of infix token pointers

    AVL<string> _field_names_tree; // avl tree containing all of the field names

    vector<string> _field_names; // vector containing all of the field names
    //{fname, lname, major}

    Map<string, long> _field_names_column_indices; // maps field names to column indices
    //{<fname, 0>, <lname, 1>, <major, 2>}

    vector<MMap<string, long> *> _index_structures; // vector of multimap pointers mapping field values to record numbers
    //<Bob, {22, 33, 55}>, <Joe, {44, 66, 77}>...

    // this is very bad and should not map to pointers
    Map<string, MMap<string, long> *> _lookup_map; // maps field names to pointers to multimaps of field values and record numbers
    //<fname, <Bob, {22, 33, 55}>, <Joe, {44, 66, 77}>...>

    // Map<long, MMap<string, long>* > indicial_lookup_map; // maps field column indices to pointers to multimaps of field values and record numbers
    //<0, <Bob, {22, 33, 55}>, <Joe, {44, 66, 77}>...>
};

// trying to construct an existing table
struct TableAlreadyExists : exception
{
    string error_message;

    TableAlreadyExists(string table_name)
    {
        error_message = "'" + table_name + "' already exists.";
    }

    const char *what() const noexcept
    {
        return error_message.c_str();
    }
};

// table file was not found
struct InvalidTable : exception
{
    string error_message;

    InvalidTable(string table_name)
    {
        error_message = "'" + table_name + "' was an invalid table.";
    }

    const char *what() const noexcept
    {
        return error_message.c_str();
    }
};

// user entered a field that was not in the table
struct InvalidField : exception
{
    string error_message;

    InvalidField(string field)
    {
        error_message = "Field '" + field + "' was invalid.";
    }

    const char *what() const noexcept
    {
        return error_message.c_str();
    }
};

#endif /* TABLE_H */
