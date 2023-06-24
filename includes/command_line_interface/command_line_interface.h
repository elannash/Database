#ifndef COMMAND_LINE_INTERFACE_H
#define COMMAND_LINE_INTERFACE_H

#include <iostream>
#include <string>
#include "../sql/sql.h"

using namespace std;

class CommandLineInterface
{
public:
    CommandLineInterface();

    void run();

private:
    SQL _sql;
};

#endif /* COMMAND_LINE_INTERFACE_H */
