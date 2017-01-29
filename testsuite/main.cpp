#include <iostream>
#include <string>
#include <fstream>

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

    std::string line;
    std::getline(testfile, line);
    std::cout << line << std::endl;

    testfile.close();


    return 0;
}
