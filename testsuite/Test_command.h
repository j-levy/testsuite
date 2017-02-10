#ifndef TEST_COMMAND_H
#define TEST_COMMAND_H

#include <iostream>
#include <string>
#include <fstream>


class Test_command
{
    public:
        //ctors
        Test_command();
        ~Test_command();

        //printer
        void print();

        //setters
        void set_command(std::string var);
        void set_provided_input(std::string var);
        void set_expected_output(std::string var);

        //we don't use getters.

        // action-takers
        int execute_test();


    protected:

    private:
        // strings that are extracts from the test file.
        std::string command;
        std::string provided_input;
        std::string expected_output;
        std::string effective_output;
};

#endif // TEST_COMMAND_H
