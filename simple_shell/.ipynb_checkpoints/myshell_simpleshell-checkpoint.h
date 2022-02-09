#ifndef MYSHELL_SIMPLESHELL_H
#define MYSHELL_SIMPLESHELL_H
#include "myshell_parser.h"
#include <stdbool.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 512
#define MAX_TOKEN_LENGTH 32

//prompts user for command input
void user_prompt(char*);

//In this case, a command takes its input from the file (not stdin). Note that spacing is irrelevant around the < operator. For example, ​cat<file​ and ​cat <file​ are valid inputs. Also, only one input redirection is allowed for a single command. (​cat<<file ​is invalid)
void execute_redirect_in(char*);

//overarching function to run shell processes
void run_shell();
#endif /* MYSHELL_SIMPLESHELL_H */
