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

#define BUFFERSIZE 12



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
        /*
        dup(fd[1]);
        dup2(fd[1],1); // duplicates file description "writer" onto "stdout"
        */
        std::string chaine_lambda = "Son to father : TOTO AIME LES BATEAUX";
        write(father_to_son[1], chaine_lambda.c_str(), sizeof(chaine_lambda));

        // LET'S READ !
        char buffer[BUFFERSIZE];
        memset(buffer, 0, sizeof(char) * (BUFFERSIZE ));
        int num_read = 1;
        while(num_read != 0)
        {
            num_read = read(father_to_son[0], &buffer, BUFFERSIZE - 1);
            buffer[num_read] = '\0';
            printf("%s", buffer);
        }

        return;
    }
    else
    {  // father talking
        close(son_to_father[1]); // father doesn't need to write where his son writes
        close(father_to_son[0]); // father doesn't need to read what he sends to his son
        /*
        // Part where we waited. No need to wait, as the read will block until the pipe contains things.

        int *son_status = NULL;
        pid_t son_pid = wait(son_status); // will return the PID of son.
        printf("Son of PID %d has returned.\n", son_pid);

        // part where you can read the file descriptor
        */

        std::string chaine_lambda = "Father to son : PAT PAT PAT";
        write(father_to_son[1], chaine_lambda.c_str(), sizeof(chaine_lambda));

        // LET'S READ !
        char buffer[BUFFERSIZE];
        memset(buffer, 0, sizeof(char) * (BUFFERSIZE ));
        int num_read = 1;
        while(num_read != 0)
        {
            num_read = read(son_to_father[0], &buffer, BUFFERSIZE - 1);
            buffer[num_read] = '\0';
            printf("%s", buffer);
        }

        return;


    }



}
