#include "main.h"
#include "Test_command.h"
#include "instruction_classify.h"


std::string getline_fromfile(std::istream &testfile, std::string read_line) // testfile should be accessed !
{

    std::getline(testfile, read_line);
    char lastChar;

    // Get the last character to see if it's a '\'. I code in C++98, so we have to use this dirty trick.
    // In C++11 there is the magical function "read_line.back()"
    if (!read_line.empty())
        lastChar = read_line.at( read_line.size() - 1 );
    else
        lastChar = 0;


    if (read_line != "" && lastChar == '\\') // '\\' means the \ char. Test if string is not empty BEFORE !
    {
        // remove backslash. we already tested, read_line is not empty to enter here.
        read_line.erase (read_line.size()-1);

        // Don't append the \n in the end of the string. That was a mistake I made when reading the subject.
        //read_line.push_back('\n');

        return read_line + getline_fromfile(testfile, read_line);
    } else {
        return read_line;
    }
}


void treat_line(char command_type, std::string read_line, Test_command &instruction)
{
    // redirection following the first character
    switch(command_type)
    {
        case '#':
            break;
        case '$':
            instruction.set_command(read_line);
            instruction.execute_test();
            break;
        case '>':
            instruction.set_expected_output(read_line);
            break;
        case '<':
            instruction.set_provided_input(read_line);
            break;
        default:
            std::cout << "ligne inconnue ! " << std::endl;
    }
}
