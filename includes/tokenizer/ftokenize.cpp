#include "ftokenize.h"

FTokenizer::FTokenizer(const char *fname) : _pos(0), _blockPos(0), _more(true)
{
    _f.open(fname);

    if (_f.fail())
    {
        cout << "Failed to open " << fname << "." << endl;
        exit(1);
    }
}

StkToken FTokenizer::next_token()
{
    StkToken t;

    if (_stk.more()) // this if else could probably be redone in a better way
    {
        _stk >> t;
        _blockPos++;
    }
    else if (get_new_block())
    {
        _stk >> t;
        _blockPos++;
    }

    return t;
}

bool FTokenizer::more()
{
    return _more;
}

int FTokenizer::pos()
{
    return _pos;
}

int FTokenizer::block_pos()
{
    return _blockPos;
}

FTokenizer &operator>>(FTokenizer &f, StkToken &t)
{
    const bool debug = false;

    t = f.next_token();

    if (debug)
    {
        cout << "pos in file: [" << f.pos() << "]" << endl
             << "pos in block: ["
             << f.block_pos() << "]" << endl;
    }

    return f;
}

bool FTokenizer::get_new_block()
{
    char *buffer = new char[MAX_BLOCK](); // new array initialized with '\0'

    _f.read(buffer, MAX_BLOCK - 1); // read the next block of the file

    _stk.set_string(buffer); // set the new string for stokenizer object

    _pos++;        // increment the position in the file
    _blockPos = 0; // reset the position in the block

    delete[] buffer;

    if (_f.gcount() == 0) // gcount returns the number of bytes read by ftk
    {
        _more = false;
        return false;
    }

    return true;
}