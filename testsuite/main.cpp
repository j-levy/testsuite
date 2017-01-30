#include <iostream>
#include <string>
#include <fstream>

#include "Test_command.h"
#include "instruction_classify.h"

int main(int argc, char **argv)
{
    std::cout << "Hello world!" << std::endl;
    std::string file = "";
    if (argc == 2)
    {
        file = argv[1];
    }
    else
    {
        file = "test01";
    }

    std::ifstream testfile;
    testfile.open(file.c_str());
    // équivalent à std::ifstream testfile(string);
    if (!testfile)
    {
        // something went wrong
        std::cout << "Something went wrong. File does not exist, or is locked.\n" << std::endl;
        return 1;
    }

    int line_counter = 0;
    Test_command instruction(line_counter);

    while(!testfile.eof())
    {
        treat_line(testfile, instruction);
    }


    testfile.close();


    return 0;
}
