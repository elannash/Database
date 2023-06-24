#ifndef FILE_RECORD_H
#define FILE_RECORD_H

#include <iostream>
#include <iomanip>
#include <string.h>
#include <cstring>
#include <vector>
#include "utilities.h"

using namespace std;

struct FileRecord
{
    static const int MAX = 100;
    int _recno;
    char _record[MAX][MAX] = {'\0'};
    int _num_of_fields;

    FileRecord() : _recno(-1), _num_of_fields(0) {}

    FileRecord(const vector<string> &v) : _recno(-1), _num_of_fields(v.size())
    {
        vector<string>::const_iterator it;
        int i;

        for (it = v.begin(), i = 0; it != v.end(); it++, i++)
            strncpy(&_record[i][0], it->c_str(), strlen(it->c_str()));
    }

    long write(fstream &outs);           // returns the record number
    long read(fstream &ins, long recno); // returns the number of bytes read
                                         // will either be MAX, or zero if read passed the end of file

    vector<string> get_record(const vector<long> &column_indices); // return vector containing all rows of record

    string operator[](int i); // return row i as a string
    friend ostream &operator<<(ostream &outs, const FileRecord &r);
};

#endif