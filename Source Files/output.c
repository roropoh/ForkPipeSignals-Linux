#include "header.h"

/*------------------------------------------------------------------------------------------------------------------ 
-- SOURCE FILE: output.c - This file is meant to hold everything that will be handled in the output
--                              process (child process) of the main process. It will print out everything
--                              that is transfered from the pipe, and will be handled by using the printf
--                              function, as well as using fflush to standard out.
-- 
-- PROGRAM: Assignment 1.exe 
-- 
-- FUNCTIONS: 
--          void output_process(int output_pipe, int c)
-- 
-- DATE: January 16, 2014 
-- 
-- DESIGNER: Robin Hsieh A00657820 
-- 
-- PROGRAMMER: Robin Hsieh A00657820 
-- 
----------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION: output_process 
-- 
-- DATE: January 16, 2014 
-- 
-- REVISIONS:  
-- 
-- DESIGNER: Robin Hsieh 
-- 
-- PROGRAMMER: Robin Hsieh 
-- 
-- INTERFACE: void output_process(int output_pipe, int c)
--              int output_pipe:    The int that will old the value for the output pipe.
--              int c:              The character value that is being passed in.
-- 
-- RETURNS: Void
-- 
-- NOTES:
-- This function is meant to printf everything that comes into the output_pipe.
-- Code can be uncommented if we want to implement the elimination of all none alphabet characters.
--
------------------------------------------------------------------------------------------------------------------*/
void output_process(int output_pipe, int c)
{
    while(1)
    {
        if(read(output_pipe, &c, 1))
        {

            // code to be used if we want to eliminate all none alphabet characters
            //if(isalpha(c) || c == '\r' ||c == '\n')
            {
                if(c == 'E' || c == 'T')
                {
                    printf("%c\r\n", c);
                    fflush(stdout);
                }
                else
                {
                    printf("%c", c);
                    fflush(stdout);
                }
            }
        }
    }
}