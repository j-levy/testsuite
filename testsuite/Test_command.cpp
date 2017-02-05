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

    if (cpid != 0) // son talking
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


        std::string reading = "";
        std::cin >> std::noskipws; // allows cin to start with spaces

        int c = 1;
        while (c != 0) // 0 AKA '\0' Bwahahaha (<= mad scientist)
        {
            c = std::cin.get();
            reading.push_back(c); // append character into the "reading" string. Also adds the '\0' for the future.
        }
        // using cerr to display messages, as cout writes into the pipe !
        std::cerr << "Son has read : " << reading << std::endl;

        // writing to father using... cout !
        std::cout << reading << " written" << std::endl;
        exit(0);
    }
    else
    {  // father talking
        close(son_to_father[1]); // father doesn't need to write where his son writes
        close(father_to_son[0]); // father doesn't need to read what he sends to his son

        std::string chaine_lambda = "   PAT \nPAT2 \n   PAT 3";
        chaine_lambda.push_back('\0');
        // OK ALORS LA METHODE .c_str() NE RAJOUTE PAS LE '\0' TOUT SEUL FAUT LE METTRE A LA MAIN OKLM
        write(father_to_son[1], chaine_lambda.c_str(),chaine_lambda.length());

        char got = 0;

        std::cout << "father reading : ";
        while (read(son_to_father[0], &got, 1))
            std::cout << got;

        return 0;
    }

}
