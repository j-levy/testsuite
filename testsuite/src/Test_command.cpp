#include "Test_command.h"

Test_command::Test_command()
{
    // initializing attributes.
    provided_input = "";
    expected_output = "";
    command = "";
}

Test_command::~Test_command()
{
    //destructor : nothing to do in particular (no free needed)
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
