#include "utilities.h"

bool file_exists(const char filename[])
{
    const bool debug = false;

    fstream ff;

    ff.open(filename, std::fstream::in | std::fstream::binary);

    if (ff.fail())
    {
        if (debug)
            cout << "file_exists(): File does NOT exist: " << filename << endl;
        return false;
    }

    if (debug)
        cout << "file_exists(): File DOES exist: " << filename << endl;

    ff.close();

    return true;
}

void open_fileRW(fstream &f, const char filename[])
{
    const bool debug = false;
    // opening a nonexistent file for in|out|app causes a fail()
    //   so, if the file does not exist, create it by opening it for
    //   output:
    if (!file_exists(filename))
    {
        // create the file
        f.open(filename, std::fstream::out | std::fstream::binary);

        if (f.fail())
        {
            string error_message = "File open (RW) failed: " + string(filename) + ".";
            throw std::runtime_error(error_message);
        }
        else
        {
            if (debug)
                cout << "open_fileRW: file created successfully: " << filename << endl;
        }
    }
    else
    {
        f.open(filename, std::fstream::in | std::fstream::out | std::fstream::binary);

        if (f.fail())
        {
            string error_message = "File open (RW) failed: " + string(filename) + ".";
            throw std::runtime_error(error_message);
        }
    }
}

void open_fileW(fstream &f, const char filename[])
{
    f.open(filename, std::fstream::out | std::fstream::binary);

    if (f.fail())
    {
        string error_message = "File open (W) failed: | " + string(filename) + ".";
        throw std::runtime_error(error_message);
    }
}

/**
 * @brief Writes each string element from vector v into its own line in a .txt file. Will create a file with the name 'filename'.txt if one does not already exist.
 *
 * @param f
 * @param filename
 * @param v
 */
void write_info(fstream &f, const char filename[], const vector<string> &v)
{
    f.open(filename, std::fstream::out);

    if (f.fail())
    {
        string error_message = "Write_info failed to open " + string(filename) + ".";
        throw std::runtime_error(error_message);
    }

    for (vector<string>::const_iterator it = v.begin(); it != v.end(); it++)
        f << *it << endl;
}

/**
 * @brief Takes each line from a file and pushes into a string vector.
 *
 * @param f
 * @param filename
 * @param v
 */
void read_info(fstream &f, const char filename[], vector<string> &v)
{
    f.open(filename);
    string field;

    if (!file_exists(filename))
    {
        string error_message = "Read info failed. File does not exist.";
        throw std::runtime_error(error_message);
    }
    if (f.fail())
    {
        string error_message = "Read_info failed to open " + string(filename) + ".";
        throw std::runtime_error(error_message);
    }

    while (getline(f, field))
        v.push_back(field);
}