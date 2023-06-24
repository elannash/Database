#include <iostream>
#include <iomanip>

#include "includes/command_line_interface/command_line_interface.h"

using namespace std;

int main(int argv, char **argc)
{
    CommandLineInterface interface;
    interface.run();

    return 0;
}
