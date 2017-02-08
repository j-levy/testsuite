#include "Test_command.h"
// includes for wait()
#include <sys/types.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdio.h> // just to test for the printf

// include for pipe, fork
#include <unistd.h>
#include <string>
// include for exit

#define BUFFERSIZE 120



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

void Test_command::print()
{
    std::cout << "Instruction contains :" << std::endl;
    if (provided_input != "")
        std::cout << "  Provided input : " << provided_input << std::endl;
    if (expected_output != "")
        std::cout << "  Expected output : " << expected_output << std::endl;
    if (command != "")
        std::cout << "  Command : " << command << std::endl;
}

void Test_command::set_command(std::string var)
{
    command = var;
    std::cout << "Set command to : " << command << std::endl;
}

void Test_command::set_provided_input(std::string var)
{
    provided_input = provided_input + var + "\n"; // manually adds \n because getline() removes it.
    std::cout << "Added " << var << "to provided input which is now : " << expected_output << std::endl;
}

void Test_command::set_expected_output(std::string var)
{
    expected_output = expected_output + var + "\n"; // manually adds \n because getline() removes it.
    std::cout << "Added " << var << "to expected output which is now : " << expected_output << std::endl;
}

int Test_command::execute_test()
{
    /*
    This method is for the moment a dummy method to test the piping between two processes.
    */
    std::cout << "Execution started." << std::endl;
    int father_to_son[2]; // two pipes : Father is Writer, Son is Reader
    int son_to_father[2]; // two pipes : Father is Reader, Son is Writer


    // THE FOLLOWING CODE IS INSPIRED FROM LINUX'S PROGRAMMER MANUAL :  "man 2 pipe" :D
    // AND FROM THE EXERCICE ABOUT "POPEN"
    int res_pipe1 = pipe(father_to_son) ;
    int res_pipe2 = pipe(son_to_father) ;
    if (res_pipe1 == -1 || res_pipe2 == -1)
    {
       perror("pipe");
       exit(EXIT_FAILURE);
    }

    int cpid = fork();
    if (cpid == -1)
    {
       perror("fork");
       exit(EXIT_FAILURE);
    }
    /* SUMMARY :
        to_son[0] = fd for SON to READ
        to_son[1] = fd for SON to WRITE
        to_father[0] = fd for FATHER to READ
        to_father[1] fd for FATHER to WRITE
    */

    if (cpid == 0) // son talking
    {
        close(son_to_father[0]); // son doesn't need to read what he sends to father
        close(father_to_son[1]); // son doesn't need to write where his father writes

        /*
        I'm a hooligan : since the process "son" doesn't need to get anything from standard input cin and send anything to standard output cout...
        I use cin and cout as file descriptors and I put the pipes in place of them. Screw you, C++ !
        */
        dup(son_to_father[1]);
        dup2(son_to_father[1],1); // duplicates file description "writer" onto "cout"
        dup(father_to_son[0]);
        dup2(father_to_son[0], 0); // duplicates file descriptor "reader" onto "cin"


        std::string m_command = "";
        std::string m_args = "";
        std::cin >> std::noskipws; // allows cin to start with spaces

        // GET COMMAND
        int c = 1;
        while (c != 0) // 0 AKA '\0'
        {
            c = std::cin.get();
            if (c != 0) // we need to remove the '\0'
                 m_command.push_back(c); // append character into the "m_command" string
        }
        // GET ARGUMENTS
        c = 1;
        while (c != 0) // 0 AKA '\0'
        {
            c = std::cin.get();
            if (c != 0) // we need to remove the '\0'
                 m_args.push_back(c); // append character into the "m_command" string
        }
        // using cerr to display messages, as cout writes into the pipe !
        std::cerr << "Son has read : " << m_command << std::endl;

        // Execution part.
        std::string shell = "sh";
        std::string shellarg = "-c";
        std::string shellcommand = m_command + " " + m_args;

        // "execlp" is a C function, coming from a world where strings are char* terminated by '\0'. We need this last char...
        shell.push_back('\0');
        shellarg.push_back('\0');
        shellcommand.push_back('\0');

        // execlp(program, arg0 (program name), arg1, ..., argn, NULL)
        // NULL is not defined so I use (void *) 0
        // I cast every string so that it matches the required type
        execlp((const char*) shell.c_str(), (const char*) shell.c_str(), (const char*) shellarg.c_str(), (const char*) shellcommand.c_str(), (void*) 0);
        return 0;
    }
    else
    {  // father talking
        close(son_to_father[1]); // father doesn't need to write where his son writes
        close(father_to_son[0]); // father doesn't need to read what he sends to his son


        // OK ALORS LA METHODE .c_str() NE RAJOUTE PAS LE '\0' TOUT SEUL FAUT LE METTRE A LA MAIN
        std::string m_command = "ls";
        m_command.push_back('\0');
        write(father_to_son[1], m_command.c_str(),m_command.length());

        std::string m_args = "-l ~";
        m_args.push_back('\0');
        write(father_to_son[1], m_args.c_str(),m_args.length());

        char got = 0;

        std::cout << "father reading : ";
        int *res = 0;
        wait(res);
        while (read(son_to_father[0], &got, 1))
            std::cout << got;

        return 0;
    }

}
