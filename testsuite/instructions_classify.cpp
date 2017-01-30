#include "main.h"
#include "Test_command.h"
#include "instruction_classify.h"

void treat_line(std::ifstream &testfile, Test_command &instruction)
{

    std::string read_line = "";
    char command_type = 0;

    testfile.get(command_type);
    std::cout << "Command char : " << command_type << " applied to : " << std::endl;
    std::getline(testfile, read_line);
    std::cout << read_line << std::endl;

    switch(command_type)
    {
        case '#':
            break;
        case '$':
            instruction.set_command(read_line);
            break;
        case '>':
            instruction.set_expected_output(read_line);
            break;
        case '<':
            instruction.set_provided_input(read_line);
            break;
    }
}
