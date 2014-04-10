#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>

#define READ_PIPE 0
#define WRITE_PIPE 1
#define BUFFER_SIZE 1024

void append(char* s, char c) ;
void backspace(char* s) ;

void catch_int () ;
void catch_usr1 () ;

void print_translate(char* buffer, int output_pipe) ;

void output_process(int output_pipe, int c) ;
void translate_process(int translate_pipe, int c, int output_pipe, char* buffer) ;

void exit_program(pid_t translateProcess, pid_t outputProcess) ;

#endif