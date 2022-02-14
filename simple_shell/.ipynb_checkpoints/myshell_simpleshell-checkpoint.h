#ifndef MYSHELL_SIMPLESHELL_H
#define MYSHELL_SIMPLESHELL_H
#include "myshell_parser.h"
#include <stdbool.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 512
#define MAX_TOKEN_LENGTH 32

//prompts user for command input
void user_prompt(char*);

void execute_command(struct pipeline_command *);

//In this case, a command takes its input from the file (not stdin). Note that spacing is irrelevant around the < operator. For example, cat<file and cat <file are valid inputs. Also, only one input redirection is allowed for a single command. (cat<<file is invalid)
int execute_redirect_in(char*);

//An input following this template indicates that a command writes its output to the specified file (not stdout). Again, spacing is irrelevant (see case a) and only one input redirection is allowed for a single command.
int execute_redirect_out(char*);

//The pipe character allows several commands to be connected, forming a pipeline. The output of the command before “|” is piped to the input of the command following “|”. A series of multiple piped commands is allowed on the command line. Spacing is irrelevant (described above). Example: cat a| sort | wc indicates that the output of the cat command is channeled to the sort and sort sends its output to the input of the wc program.
int* execute_pipeline();

//The ampersand character '&’ should allow the user to execute a command (or pipeline of commands) in the background. In this case, the shell immediately displays a prompt for the next line regardless of whether the commands on the previous line have finished or are still in progress
void execute_background(char*);

void reset_inout(int, int);
//overarching function to run shell processes
void run_shell();
#endif /* MYSHELL_SIMPLESHELL_H */
