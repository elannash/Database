#ifndef STATEMACHINEFUNCTIONS_H
#define STATEMACHINEFUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <cstring>
#include "constants.h"

using namespace std;

// Fill all cells of the array with -1
void init_table(int _table[][MAX_COLUMNS]);

// Mark this state (row) with a 1 (success)
void mark_success(int _table[][MAX_COLUMNS], int state);

// Mark this state (row) with a 0 (fail)
void mark_fail(int _table[][MAX_COLUMNS], int state);

// true if state is a success state
bool is_success(int _table[][MAX_COLUMNS], int state);

// Mark a range of cells in the array.
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state);

// Mark columns represented by the string columns[] for this row
void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state);

// Mark this row and column
void mark_cell(int row, int _table[][MAX_COLUMNS], int column, int state);

// Print the table from col1 to col2 (down to row)
void print_table(int _table[][MAX_COLUMNS], int col1, int col2, int row);

// show string s and mark this position on the string:
// hello world   pos: 7
//        ^
void show_string(char s[], int _pos);

#endif /* STATEMACHINEFUNCTIONS_H */
