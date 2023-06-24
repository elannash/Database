#include "file_record.h"

long FileRecord::write(fstream &outs)
{
    outs.seekg(0, outs.end); // we start writing from the end of the file

    long pos = outs.tellp(); // set pos to the beginning of where we will write from

    for (int i = 0; i < sizeof(_record) / sizeof(_record[0]); i++) // loop through all fields of the record (even the ones not being used) and write to file
        outs.write(&_record[i][0], sizeof(_record[i]));            // write the ith row into file

    return pos / sizeof(_record); // record number
}

long FileRecord::read(fstream &ins, long recno)
{
    _num_of_fields = 0; // should probably figure out a better way to handle _num_of_fields

    long pos = recno * sizeof(_record); // find the starting position of the record
    ins.seekg(pos, ios_base::beg);      // and go to it

    for (int i = 0; i < sizeof(_record) / sizeof(_record[0]); i++) // loop through the file and fill in all fields of the record (even the ones not being used)
    {
        ins.read(&_record[i][0], sizeof(_record[i])); // read the ith row into record

        if (_record[i][0] != '\0')
            _num_of_fields++;
    }

    return ins.gcount(); // bytes read
}

vector<string> FileRecord::get_record(const vector<long> &column_indices)
{
    vector<string> v; // vector of field values in the record

    for (long index : column_indices) // for each field in the record, push back the corresponding field value into a vector of strings
        v.push_back(&_record[index][0]);

    return v;
}

string FileRecord::operator[](int i)
{
    return string(&_record[i][0]);
}

ostream &operator<<(ostream &outs, const FileRecord &r)
{
    for (int i = 0; i < sizeof(r._record[0]); i++)
    {
        if (r._record[i][0] != '\0') // print the fields that are being used
            outs << setw(25) << r._record[i];
    }

    return outs;
}
