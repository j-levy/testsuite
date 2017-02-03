#ifndef INSTRUCTION_CLASSIFY_H_INCLUDED
#define INSTRUCTION_CLASSIFY_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>

std::string getline_fromfile(std::istream &testfile, std::string read_line);
void treat_line(char command_type, std::string read_line, Test_command &instruction);


#endif // INSTRUCTION_CLASSIFY_H_INCLUDED
