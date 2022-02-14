#ifndef MYSHELL_SIMPLESHELL_H
#define MYSHELL_SIMPLESHELL_H
#include "myshell_parser.h"
#include <stdbool.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 512
#define MAX_TOKEN_LENGTH 32

//prompts user for command input
int user_prompt(char*);
void execute_pipeline(struct pipeline *);
int execute_command(struct pipeline_command *, int, int, int);
void run_shell();
#endif /* MYSHELL_SIMPLESHELL_H */