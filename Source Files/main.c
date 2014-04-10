#include "header.h"

/*------------------------------------------------------------------------------------------------------------------ 
-- SOURCE FILE: main.c - This application is to 
-- 
-- PROGRAM: Assignment 1.exe 
-- 
-- FUNCTIONS: 
--      int main()
--      void catch_usr1 (int signo)
--      void catch_int (int signo) 
--      void exit_program(pid_t translateProcess, pid_t outputProcess)
-- 
-- DATE: January 16, 2014 
-- 
-- DESIGNER: Robin Hsieh A00657820 
-- 
-- PROGRAMMER: Robin Hsieh A00657820 
-- 
-- NOTES: 
-- This program will take in user input, output it to stdout, translate the message, then print to stdout again.
-- All using forks, pipes, and signals.
-- 
----------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION: main 
-- 
-- DATE: January 16, 2014 
-- 
-- REVISIONS:  
-- 
-- DESIGNER: Robin Hsieh 
-- 
-- PROGRAMMER: Robin Hsieh 
-- 
-- INTERFACE: int main()
-- 
-- RETURNS: int - Returns 0 when the program ends.
-- 
-- NOTES:
-- This function is the main function of the program. It will create 2 pipes, 3 processes, and listen to 2 signals.
-- The 2 pipes will be used to transfer characters to translate and output processes. The 3 processes being created
-- are the translate process, and the output process (the main process is a process it self). And the 2 signals 
-- that are being waited upon is the signal ctrl+c that the user can use, as well as when the user decides to 
-- terminates the program.
--
------------------------------------------------------------------------------------------------------------------*/
int main()
{
    system("stty raw igncr -echo");

    pid_t childpid = 0;
    pid_t outputProcess = 0;
    pid_t translateProcess = 0;
    int i = 0;
    int c = 0;

    char buffer[BUFFER_SIZE] = "";

    int output_pipe[2];
    int translate_pipe[2];

    signal(SIGINT, catch_int);
    signal(SIGUSR1, catch_usr1);

    //creating the output pipe
    if(pipe(output_pipe) < 0)
    {
        perror("pipe call");
        exit(1);
    }

    //creating the translate pipe
    if(pipe(translate_pipe) < 0)
    {
        perror("pipe call");
        exit(1);
    }

    for(i = 1; i <3; i++)
    {
        if((childpid = fork()) <= 0)
        {
            if(i == 1)
            {
                outputProcess = getpid();
            }
            else if(i == 2)
            {
                translateProcess = getpid();
            }
            break;
        }
    }
    if(getpid() == outputProcess)
    {
        // Output Process
        output_process(output_pipe[READ_PIPE], c);
    }
    else if(getpid() == translateProcess)
    {
        // Translate Process
        translate_process(translate_pipe[READ_PIPE], c, output_pipe[WRITE_PIPE], buffer);
    }
    else
    {
        //Main Process
        while((c = getchar()) != EOF)
        {
            if(c == 11)
            {
                printf("\r\n");
                fflush(stdout);
                exit_program(translateProcess, outputProcess);
            }
            
            write(output_pipe[WRITE_PIPE], &c, 1);
            write(translate_pipe[WRITE_PIPE], &c, 1);

            if(c == 'T')
            {
                exit_program(translateProcess, outputProcess);
            }
        }
    }
    return 0;
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION: catch_usr1 
-- 
-- DATE: January 16, 2014 
-- 
-- REVISIONS:  
-- 
-- DESIGNER: Robin Hsieh 
-- 
-- PROGRAMMER: Robin Hsieh 
-- 
-- INTERFACE: void catch_usr1 ()
-- 
-- RETURNS: Void
-- 
-- NOTES:
-- This function will simply exit the process that is being called, so it does a clean terminal/kill.
--
------------------------------------------------------------------------------------------------------------------*/
void catch_usr1 ()
{
    exit(0);
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION: catch_int 
-- 
-- DATE: January 16, 2014 
-- 
-- REVISIONS:  
-- 
-- DESIGNER: Robin Hsieh 
-- 
-- PROGRAMMER: Robin Hsieh 
-- 
-- INTERFACE: void catch_int ()
-- 
-- RETURNS: Void
-- 
-- NOTES:
-- This function will catch all the signals being typed/sent by the user. Once a signal is caught, it will simply
-- wait for another signal and not handle the signals at all.
--
------------------------------------------------------------------------------------------------------------------*/
void catch_int () 
{
    signal (SIGINT, catch_int);
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION: exit_program 
-- 
-- DATE: January 16, 2014 
-- 
-- REVISIONS:  
-- 
-- DESIGNER: Robin Hsieh 
-- 
-- PROGRAMMER: Robin Hsieh 
-- 
-- INTERFACE: void exit_program(pid_t translateProcess, pid_t outputProcess)
--              pid_t translateProcess:     The PID number for the translate process.
--              pid_t outputProcess:        The PID number for the output process.
-- 
-- RETURNS: Void
-- 
-- NOTES:
-- This function will kill all the processes properly, and in order on which will be depended on. It will also
-- restore the system call to turn all the settings back to normal
--
------------------------------------------------------------------------------------------------------------------*/
void exit_program(pid_t translateProcess, pid_t outputProcess)
{
    system("stty -raw -igncr echo");
    kill(translateProcess, SIGUSR1);
    kill(outputProcess, SIGUSR1);
    exit(0);
}