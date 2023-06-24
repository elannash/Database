#include "table.h"

long Table::_serial = 0;

Table::Table() : _total_records(0), _table_name("_unnamed"), _bin_file_name("./build/bin/" + _table_name + ".tbl"), _txt_file_name("./build/bin/" + _table_name + ".txt") {}

Table::Table(string table_name) : _total_records(0), _table_name(table_name), _bin_file_name("./build/bin/" + _table_name + ".tbl"), _txt_file_name("./build/bin/" + _table_name + ".txt")
{
    fstream fields;
    vector<string> field_names;

    // removing any spaces from file names, useful when deleting files
    _bin_file_name.erase(remove(_bin_file_name.begin(), _bin_file_name.end(), ' '), _bin_file_name.end());
    _txt_file_name.erase(remove(_txt_file_name.begin(), _txt_file_name.end(), ' '), _txt_file_name.end());

    // throw exception if trying to open a table that does not exist
    if (!file_exists(_bin_file_name.c_str()))
        throw InvalidTable(table_name);

    read_info(fields, _txt_file_name.c_str(), field_names);

    set_fields(field_names);
    reindex(); // rebuild the index structures
}

Table::Table(string table_name, const vector<string> &field_names) : _total_records(0), _table_name(table_name), _bin_file_name("./build/bin/" + _table_name + ".tbl"), _txt_file_name("./build/bin/" + _table_name + ".txt")
{
    fstream bfile;
    fstream fields;

    ++_serial;

    // removing any spaces from  _bin_file_name, useful when deleting files
    _bin_file_name.erase(remove(_bin_file_name.begin(), _bin_file_name.end(), ' '), _bin_file_name.end());
    _txt_file_name.erase(remove(_txt_file_name.begin(), _txt_file_name.end(), ' '), _txt_file_name.end());

    // throw exception if trying to create a table that alredy exists
    if (file_exists(_bin_file_name.c_str())) // comment this for grader
        throw TableAlreadyExists(table_name);

    set_fields(field_names); // set internal _field_names vector and set up _index_structures and _lookup_map

    open_fileW(bfile, _bin_file_name.c_str());
    write_info(fields, _txt_file_name.c_str(), _field_names);
}

Table::~Table()
{
    clear_table();
}

Table::Table(const Table &other)
{
    copy_table(other);
}

Table Table::operator=(const Table &rhs)
{
    if (this == &rhs)
        return *this;
    else
    {
        clear_table();
        copy_table(rhs);

        return *this;
    }
}

vector<string> Table::get_fields() const
{
    return _field_names;
}

void Table::insert_into(vector<string> field_values)
{
    assert(field_values.size() <= _field_names.size() && "Number of field values provided exceeded the number of table columns");

    FileRecord r; // load the field values into the record
    fstream f;
    long recno;
    long i; // index

    // exceptionally lazy
    while (field_values.size() < _field_names.size())
        field_values.push_back("NOVALUE");

    r = FileRecord(field_values);

    open_fileRW(f, _bin_file_name.c_str());
    recno = r.write(f); // write the field values into the file and store the record number in recno

    i = 0;
    for (string str : field_values) // for each value in field values, add to the index structures
    {
        (*_index_structures[i])[r[i]] += recno; // for each index structure, map the appropriate record number to the appropriate field value
        ++i;
    }

    _total_records++;
}

Table Table::select_all()
{
    return select(_field_names);
}

Table Table::select(const vector<string> &field_names)
{
    assert(field_names.size() <= _field_names.size() && "Number of field names provided exceeded the number of table columns");

    vector<long> recnos;

    // this should work as long as i handle removal of records correctly
    for (long i = 0; i < _total_records; i++)
        recnos += i;

    _last_selected_recnos = recnos;

    return vector_to_table(field_names, recnos);
}

Table Table::select(const vector<string> &field_names, string field, string op, string value)
{
    assert(field_names.size() <= _field_names.size() && "Number of field names provided exceeded the number of table columns");

    Queue<Token *> infix_tokens;
    Queue<Token *> postfix_tokens;
    vector<long> recnos;
    vector<string> conditions;

    // infix_tokens.push(new TokenStr(field));
    // infix_tokens.push(new Relational(field));
    // infix_tokens.push(new TokenStr(field));
    conditions.push_back(field);
    conditions.push_back(op);
    conditions.push_back(value);

    infix_tokens = tokenize(conditions);

    ShuntingYard sy(infix_tokens);
    postfix_tokens = sy.postfix();
    recnos = cond(postfix_tokens);

    for (Token *delete_me : infix_tokens) // release the memory here
        delete delete_me;

    _last_selected_recnos = recnos;

    return vector_to_table(field_names, recnos); // this should return a copy of a table containing passed in fields
}

Table Table::select(const vector<string> &field_names, const Queue<Token *> &postfix)
{
    assert(field_names.size() <= _field_names.size() && "Number of field names provided exceeded the number of table columns");

    vector<long> recnos;
    recnos = cond(postfix);

    for (Token *delete_me : postfix) // release the memory here (sy is currently handling left and right parentheses)
        delete delete_me;            // and rpn will handle ResultSets

    _last_selected_recnos = recnos;

    return vector_to_table(field_names, recnos);
}

Table Table::select(const vector<string> &field_names, const vector<string> &infix_strings)
{
    assert(field_names.size() <= _field_names.size() && "Number of field names provided exceeded the number of table columns");

    Queue<Token *> infix_tokens;
    Queue<Token *> postfix_tokens;

    infix_tokens = tokenize(infix_strings);

    ShuntingYard sy(infix_tokens);
    postfix_tokens = sy.postfix();

    return select(field_names, postfix_tokens);
}

vector<long> Table::select_recnos() const
{
    return _last_selected_recnos;
}

void Table::copy_table(const Table &rhs)
{
    long i;

    _table_name = rhs._table_name;
    _bin_file_name = rhs._bin_file_name;
    _txt_file_name = rhs._txt_file_name;

    _total_records = rhs._total_records;
    _last_selected_recnos = rhs._last_selected_recnos;
    _field_names_tree = rhs._field_names_tree;
    _field_names = rhs._field_names;
    _field_names_column_indices = rhs._field_names_column_indices;

    i = 0;
    for (string str : _field_names)
    {
        _index_structures.push_back(new MMap<string, long>(*rhs._index_structures[i]));
        _lookup_map[str] = _index_structures[i];
        ++i;
    }
}

void Table::clear_table()
{
    _table_name = "_unnamed";
    _bin_file_name = _table_name + ".tbl";
    _txt_file_name = _table_name + ".txt";

    for (MMap<string, long> *index_structure : _index_structures)
        delete index_structure;

    _total_records = 0;
    _last_selected_recnos.clear();

    _field_names.clear();
    _field_names_tree.clear();
    _field_names_column_indices.clear();
    _index_structures.clear();
    _lookup_map.clear();
}

void Table::set_fields(const vector<string> &field_names)
{
    long i; // index being mapped to field

    i = 0;                      // start indexing from 0
    _field_names = field_names; // store field names in private member vector
    //_index_structures.resize(_field_names.size()); // resize _index_structures so we can avoid reallocation during loop ONLY NEED IF USING MMAPS INSTEAD OF MMAP POINTERS IN INDEX_STRUCTURES

    // build tree that holds field names
    // build vector of MMaps
    // build vector of field name column indices
    // build map of strings to index structures
    for (string field : _field_names)
    {
        _field_names_tree.insert(field);
        _index_structures.push_back(new MMap<string, long>()); // push new MMap into vector
        _field_names_column_indices[field] = i;                // map field to its column index in the table
        _lookup_map[field] = _index_structures[i];             // map each string in _field_names to the appropriate index structure
        ++i;
    }
}

void Table::reindex()
{
    fstream bfile;
    FileRecord r;
    long recno;
    long bytes;
    int i;

    open_fileRW(bfile, _bin_file_name.c_str());

    recno = 0;
    bytes = r.read(bfile, recno);
    while (bytes > 0) // read the entire file
    {
        i = 0;
        for (string field : _field_names) // for each field in our table, add the field values of the current record being read
        {
            (*_index_structures[i])[r[i]] += recno;
            ++i;
        }
        ++recno;
        bytes = r.read(bfile, recno);
    }

    _total_records = recno; // total records will be the number of the last record inserted
}

vector<long> Table::cond(const Queue<Token *> &postfix) const
{
    RPN rpn(postfix); // RPN takes postfix queue for evaluation

    return rpn(_lookup_map); // RPN () operator calls its evaluate function, takes lookup_map and returns vector of record numbers
}

Table Table::vector_to_table(const vector<long> &recnos) const
{
    return vector_to_table(_field_names, recnos);
}

Table Table::vector_to_table(const vector<string> &field_names, const vector<long> &recnos) const
{
    Table return_table(string("_select_" + _table_name + to_string(_serial)), field_names);
    FileRecord r;
    fstream f;
    vector<long> column_indices;

    open_fileRW(f, _bin_file_name.c_str());

    // for each string in the field names vector, push the corresponding index into an column indices vector
    for (string field : field_names)
    {
        // if (_field_names_column_indices.contains(field)) // delete this if condition
            column_indices.push_back(_field_names_column_indices[field]);
    }

    // for each record number in the recnos vector, read the corresponding record from the file and insert the vector of strings returned by r.get_record() into the return table
    for (long recno : recnos)
    {
        r.read(f, recno);
        return_table.insert_into(r.get_record(column_indices));
    }

    return return_table;
}

Queue<Token *> Table::tokenize(const vector<string> &infix_strings) const
{
    Queue<Token *> infix_tokens;

    for (string str : infix_strings)
    {
        if (str == "=")
            infix_tokens.push(new Relational(str));
        else if (str == ">=")
            infix_tokens.push(new Relational(str));
        else if (str == "<=")
            infix_tokens.push(new Relational(str));
        else if (str == ">")
            infix_tokens.push(new Relational(str));
        else if (str == "<")
            infix_tokens.push(new Relational(str));
        else if (str == "and")
            infix_tokens.push(new Logical(str));
        else if (str == "or")
            infix_tokens.push(new Logical(str));
        else if (str == "(")
            infix_tokens.push(new LeftParen());
        else if (str == ")")
            infix_tokens.push(new RightParen());
        else
            infix_tokens.push(new TokenStr(str));
    }

    return infix_tokens;
}
