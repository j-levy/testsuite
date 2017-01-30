#include "Test_command.h"

Test_command::Test_command(int current_line)
{
    provided_input = "";
    expected_output = "";
    command = "";
}

Test_command::~Test_command()
{
    //dtor
}

void Test_command::set_command(std::string var)
{
    command = var;
}

void Test_command::set_provided_input(std::string var)
{
    provided_input = var;
}

void Test_command::set_expected_output(std::string var)
{
    expected_output = var;
}
