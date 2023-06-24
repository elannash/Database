#include "command_line_interface.h"

CommandLineInterface::CommandLineInterface() {}

void CommandLineInterface::run()
{
    string command;
    bool run = true;

    cout << "Type 'exit' to quit." << endl;

    while (run)
    {
        cout << ">";
        getline(cin, command);

        if (command == "exit")
            run = false;
        else
        {
            try
            {
                cout << _sql.command(command) << endl;
            }
            catch (const exception &e)
            {
                cerr << e.what() << endl;
            }
        }
    }
}
