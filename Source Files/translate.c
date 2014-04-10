#include "header.h"

/*------------------------------------------------------------------------------------------------------------------ 
-- SOURCE FILE: translate.c - This file is meant to hold everything that will be handled in the translate
--                              process (child process) of the main process. It will take in the character
--                              being input by the user, and manipulate it as was stated in the original
--                              constraints of this assignment.
-- 
-- PROGRAM: Assignment 1.exe 
-- 
-- FUNCTIONS: 
--          void translate_process(int translate_pipe, int c, int output_pipe, char* buffer)
--          void append(char* s, char c)
--          void backspace(char* s)
--          void print_translate(char* buffer, int pipe)
-- 
-- DATE: January 16, 2014 
-- 
-- DESIGNER: Robin Hsieh A00657820 
-- 
-- PROGRAMMER: Robin Hsieh A00657820 
-- 
----------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION: translate_process 
-- 
-- DATE: January 16, 2014 
-- 
-- REVISIONS:  
-- 
-- DESIGNER: Robin Hsieh 
-- 
-- PROGRAMMER: Robin Hsieh 
-- 
-- INTERFACE: void translate_process(int translate_pipe, int c, int output_pipe, char* buffer)
--              int translate_pipe:     The int that will old the value for the translate pipe.
--              int c:                  The character value that is being passed in.
--              int output_pipe:        The int that will old the value for the output pipe.
--              char* buffer:           The char array that the buffer will be manipulated.
-- 
-- RETURNS: Void
-- 
-- NOTES:
-- This function will handle all the scenarios that the user inputs.
-- Code can be uncommented if we want to implement the elimination of all none alphabet characters.
--
------------------------------------------------------------------------------------------------------------------*/
void translate_process(int translate_pipe, int c, int output_pipe, char* buffer)
{
    while(1)
    {
        if(read(translate_pipe, &c, 1))// && isalpha(c))
        {   
            if(c == 'E')
            {
                //translate a to z and print
                append(buffer, '\r');
                append(buffer, '\n');
                print_translate(buffer, output_pipe);
            }
            else if(c == 'X')
            {
                backspace(buffer);
            }
            else if(c == 'K')
            {
                buffer[0] = '\r';
                buffer[1] = '\n';
                buffer[2] = '\0';
                print_translate(buffer, output_pipe);
            }
            else if(c == 'T')
            {
                append(buffer, '\r');
                append(buffer, '\n');
                print_translate(buffer, output_pipe);
            }
            else
            {
                append(buffer, c);
            }
        }
    }
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION: append 
-- 
-- DATE: January 16, 2014 
-- 
-- REVISIONS:  
-- 
-- DESIGNER: Robin Hsieh 
-- 
-- PROGRAMMER: Robin Hsieh 
-- 
-- INTERFACE: void append(char* s, char c)
--              char* s:    The char array that will be being appended to.
--              char c:     The character that we want to append to the string.
-- 
-- RETURNS: Void
-- 
-- Notes: 
-- This function will take a single character, and append it to the end of a string.
--
------------------------------------------------------------------------------------------------------------------*/
void append(char* s, char c)
{
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION: backspace 
-- 
-- DATE: January 16, 2014 
-- 
-- REVISIONS:  
-- 
-- DESIGNER: Robin Hsieh 
-- 
-- PROGRAMMER: Robin Hsieh 
-- 
-- INTERFACE: void backspace(char* s)
--              char* s:    The char array that will be being manipulated on.
-- 
-- RETURNS: Void
-- 
-- Notes:
-- This function will remove the last character of the string at this point (same funcationally as backspace).
--
------------------------------------------------------------------------------------------------------------------*/
void backspace(char* s)
{
    if(strlen(s) > 0)
    {
        int len = strlen(s);
        s[len-1] = '\0';
    }
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION: print_translate 
-- 
-- DATE: January 16, 2014 
-- 
-- REVISIONS:  
-- 
-- DESIGNER: Robin Hsieh 
-- 
-- PROGRAMMER: Robin Hsieh 
-- 
-- INTERFACE: void print_translate(char* buffer, int pipe)
--              char* buffer:           The char array that will be manipulated.
--              int pipe:               The pipe that will be used to write into.
-- 
-- RETURNS: Void
-- 
-- Notes: 
-- This function will take in the buffer that has already been appended to, and change all the 'a' to 'z'.
-- Then will be written to the pipe, as well as clearing the buffer.
--
------------------------------------------------------------------------------------------------------------------*/
void print_translate(char* buffer, int pipe)
{
    unsigned int j = 0;
    for(j = 0; j < strlen(buffer); j++)
    {
    if(buffer[j] == 'a')
        {
            buffer[j] = 'z';
        }
    }

    write(pipe, buffer, strlen(buffer));

    //clear buffer
    buffer[0] = '\0';
}
