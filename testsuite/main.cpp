#include <iostream>
#include <string>
#include <fstream> // manages files

#include "Test_command.h"
#include "instruction_classify.h"

int main(int argc, char **argv)
{
    std::cout << "Hello world!" << std::endl;

    std::string file = "";
    // gets the name of the test file to open, or open a dummy file otherwise (useful when compiling/testing...)
    if (argc == 2) // exactly 2 arguments : the name of the program itself, and the file to open
    {
        file = argv[1]; // get its name (as a string)
    }
    else
    {
        file = "test01"; // dummy file
    }

    /*
    File definition and opening :
    Here, we define an ifstream object (IFstream = Input File stream)
    We try to open the file we passed (or the dummy file).
    If something goes wrong, we end the program with an error code.
    */
    std::ifstream testfile;
    testfile.open(file.c_str());
    // equivalent to: std::ifstream testfile(string);

    if (!testfile)
    {
        // something went wrong
        std::cout << "Something went wrong. File does not exist, or is locked.\n" << std::endl;
        return 1;
    }

    /*
    We came this far, so we can read the file !
    Class Test_command is here to gather all the information needed for a command.
    treat_line takes an ifstream object and a Test_command object, and reads a line from the file, then places it into the Test_command object.
    */
    Test_command instruction;
    std::string read_line;
    char command_type;
    // about "eof" : remember that files have a virtual cursor pushing forwards at each read/write. Here we read.

    while(!testfile.eof())
    {
        command_type = 0;
        read_line = "";

         // get first non-space, non-return character into the char command_type
        do {
            testfile.get(command_type);
        } while (command_type == ' ' || command_type == '\n');

        if (command_type == 0) //Reached the end of the file
            break; // out of the loop (we don't need to read the next line)

        /*
        Here, we have to deal with the '\' sign.
        Basically, we can try to get the last character, and if it is a '\', read the next line, and apply... until we find a line with normal terminal char.
        This is the perfect job for a recursive function !
        */

        read_line = getline_fromfile(testfile, ""); // this trick is because recursive function is recursive :D

        // this is debug.
        std::cout << "Command char : " << command_type << " applied to : " << std::endl;
        std::cout << read_line  << std::endl;

        // here we assign the command where it should be.
        treat_line(command_type, read_line, instruction);
    }


    /// NOT READY YET
    instruction.execute_test();
    // close the file.
    testfile.close();


    return 0;
}
