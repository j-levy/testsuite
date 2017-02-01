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

    // about "eof" : remember that files have a virtual cursor pushing forwards at each read/write. Here we read.
    while(!testfile.eof()) // loop until the end of the file.
    {
        treat_line(testfile, instruction);
    }

    // close the file.
    testfile.close();


    return 0;
}
