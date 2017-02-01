#include "main.h"
#include "Test_command.h"
#include "instruction_classify.h"

void treat_line(std::ifstream &testfile, Test_command &instruction)
{

    std::string read_line = "";
    char command_type = 0;

     // get first non-space, non-return character into the char command_type
    do {
        testfile.get(command_type);
    } while (command_type == ' ' || command_type == '\n');

    if (command_type == 0) //Reached the end of the file
        return;

    // get the rest of the line
    std::getline(testfile, read_line);

    /*
    Here, we have to deal with the '\' sign.
    Basically, we can try to get the last character, and if it is a '\', read the next line, and apply... until we find a line with normal terminal char.
    maybe with another function called recursively ?
    */



    std::cout << "Command char : " << command_type << " applied to : " << std::endl;
    std::cout << read_line  << std::endl;

    // redirection following the first character
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
