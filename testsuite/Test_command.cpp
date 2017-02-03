#include "Test_command.h"
// includes for wait()
#include <sys/types.h>
#include <sys/wait.h>

// include for pipe, fork
#include <unistd.h>
#include <string.h>
// include for exit
#include <stdlib.h>
#include <stdio.h> // just to test for the printf

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

void Test_command::execute_test()
{
    /*
    This method is for the moment a dummy method to test the piping between two processes.
    */
    std::cout << "Execution started." << std::endl;
    int father_to_son[2]; // two pipes : Father is Writer, Son is Reader
    int son_to_father[2]; // two pipes : Father is Reader, Son is Writer


    // THE FOLLOWING CODE IS INSPIRED FROM LINUX'S PROGRAMMER MANUAL :  "man 2 pipe" :D
    // AND FROM THE EXERCICE ABOUT "POPEN"
    if (pipe(father_to_son) == -1 || pipe(son_to_father))
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

        /* // redirecting the file descriptor. This is for the future.
        dup(fd[1]);
        dup2(fd[1],1); // duplicates file description "writer" onto "stdout"
        */

        std::string reading = "";

        char got = 0;
        while (read(father_to_son[0], &got, 1))
            reading.push_back(got);

        int res = 1;
        std::cout << reading << " read."<< std::endl << std::flush;

        write(son_to_father[1], reading.c_str(), reading.length());
        /// Something went wrong while writing, because the next line doesn't show.
        /// Plus, the father program cannot read. The write might has gone wrong.
        /// Even when removing the "read" in the father program, the following line never show, but the program finishes.

        std::cout << reading << " written with result "<< res << std::endl << std::flush;

    }
    else
    {  // father talking
        close(son_to_father[1]); // father doesn't need to write where his son writes
        close(father_to_son[0]); // father doesn't need to read what he sends to his son

        std::string chaine_lambda = "Father to son : PAT PAT PAT";
        write(father_to_son[1], chaine_lambda.c_str(), chaine_lambda.length());

        /// displays :
        std::cout << "Father, PID " << getpid() << " reads : " << std::endl << std::flush;

        char got = 0;

        /// When coming to the next "read", the program halts
        /// I noticed that the program halts to the "read" (doesn't enter in the while loop)
        /// Is the pipe empty ? Has something emptied the pipe ?

        while (read(son_to_father[0], &got, 1))
            std::cout << got;
    }

}
