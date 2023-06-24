#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

bool file_exists(const char filename[]);

void open_fileRW(fstream &f, const char filename[]);
void open_fileW(fstream &f, const char filename[]);

void write_info(fstream &f, const char filename[], const vector<string> &v);
void read_info(fstream &f, const char filename[], vector<string> &v);

// this is so lazy
struct InvalidFile : exception
{
    string error_message;

    InvalidFile(const char *filename)
    {
        error_message = string(filename) + " is not an existing file.";
    }

    const char *what() const noexcept
    {
        return error_message.c_str();
    }
};

#endif