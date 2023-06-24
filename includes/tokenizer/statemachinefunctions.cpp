#include "statemachinefunctions.h"

void init_table(int _table[][MAX_COLUMNS])
{
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
            _table[i][j] = -1;
    }
}

void mark_success(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0] = 1;
}

void mark_fail(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0] = 0;
}

bool is_success(int _table[][MAX_COLUMNS], int state)
{
    return _table[state][0] == 1;
}

void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state)
{
    for (int i = from; i <= to; i++)
        mark_cell(row, _table, i, state);
}

void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state)
{
    for (int i = 0; i < strlen(columns); i++)
        mark_cell(row, _table, columns[i], state);
}

void mark_cell(int row, int _table[][MAX_COLUMNS], int column, int state)
{
    _table[row][column] = state;
}

void print_table(int _table[][MAX_COLUMNS], int from, int to_col, int to_row)
{
    assert(to_col < MAX_COLUMNS && "to_col should not be greater than MAX_COLS");
    assert(to_row < MAX_ROWS && "to_row should not be greater than MAX_COLS");

    for (int i = 0; i <= to_row; i++)
    {
        for (int j = from; j <= to_col; j++)
        {
            cout << setw(2) << "[ " << setw(2)
                 << _table[i][j] << setw(2)
                 << "]";
        }

        cout << endl;
    }
}

void show_string(char s[], int _pos)
{
    for (int i = 0; i < strlen(s); i++)
        cout << s[i];

    cout << '\t' << "Position: " << _pos << endl;

    for (int i = 0; i < _pos; i++)
        cout << " ";

    cout << "^" << endl;
}