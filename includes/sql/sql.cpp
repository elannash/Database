#include "sql.h"

SQL::SQL() {}

SQL::SQL(const char *file_name)
{
    batch_mode(file_name);
}

SQL::~SQL()
{
    system("includes/sql/delete_files.sh"); // call to shell script that deletes files that follow _select_*.* pattern
}

Table SQL::command(string command)
{
    _parser = Parser(command);

    if (_parser.fail())
        throw InvalidCommand(command);

    _ptree = _parser.parse_tree();

    if (_ptree["command"][0] == "make" || _ptree["command"][0] == "create")
        return make_table();
    else if (_ptree["command"][0] == "insert")
        return insert_into_table();
    else // if (_ptree["command"][0] == "select")
        return select_from_table();

    // delete
    // drop
    // load
    // save
    // print
}

void SQL::batch_mode(const char *file_name)
{
    FTokenizer _ftk(file_name);
    StkToken token;
    string sql_command;
    int query_number;

    query_number = 0;
    sql_command = "";

    // this could be better
    // assumes any line of text not commented out is a command

    _ftk >> token; // grab the first token, need to do this outside the loop for _ftk.more() to work correctly
    while (_ftk.more())
    {
        if (token.token_str() == "\n") // if the token is a new line, just print it
            cout << token;
        else if (token.token_str() == "//") // if the token is the beginning of a comment, grab tokens and print them until new line
        {
            while (_ftk.more() && token.token_str() != "\n")
            {
                cout << token;
                _ftk >> token;
            }

            cout << token; // print the new line character
        }
        else
        {
            sql_command = "";

            while (_ftk.more() && token.token_str() != "\n")
            {
                sql_command += token.token_str();
                _ftk >> token;
            }

            cout << "[" << query_number << "] " << sql_command << endl
                 << command(sql_command) << endl;

            ++query_number;
        }

        _ftk >> token; // grab the next token at the end of the loop, this will prevent trash token from being checked once ftk reaches the end of file
    }
}

Table SQL::make_table()
{
    string table_name;
    vector<string> field_names;

    table_name = _ptree["table_name"][0];
    field_names = _ptree["col"];

    _table = Table(table_name, field_names);

    return _table;
}

Table SQL::insert_into_table()
{
    string table_name;
    vector<string> field_values;

    table_name = _ptree["table_name"][0];
    field_values = _ptree["values"];

    _table = Table(table_name);

    // check if values given by the user exceed the number of columns in the table
    if (field_values.size() > _table.get_fields().size())
    {
        int last_valid_element_index = _table.get_fields().size() - 1;
        throw TooManyValues(field_values[last_valid_element_index]);
    }

    _table.insert_into(field_values);

    return _table;
}

Table SQL::select_from_table()
{
    Table select_table;
    string table_name;
    vector<string> field_names;

    table_name = _ptree["table_name"][0];
    field_names = _ptree["fields"];

    _table = Table(table_name); // open the table

    if (_ptree["fields"][0] == "*")
    {
        field_names = _table.get_fields(); // * signifies all fields so we grab all fields from the table

        if (_ptree.contains("where")) // check if condition was passed in
        {
            vector<string> condition;
            condition = _ptree["condition"];

            select_table = _table.select(field_names, condition);
        }
        else
            select_table = _table.select_all();
    }
    else
    {
        // check if fields given by user are valid, throw exception if they are not
        for (string field : field_names)
        {
            AVL<string> field_names_tree = _table.get_field_names_tree();

            if (!field_names_tree.contains(field))
                throw InvalidField(field);
        }

        if (_ptree.contains("where")) // check if condition was passed in
        {
            vector<string> condition;
            condition = _ptree["condition"];

            select_table = _table.select(field_names, condition);
        }
        else
            select_table = _table.select(field_names);
    }

    return select_table;
}
