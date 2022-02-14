#include "myshell_simpleshell.h"
#include "myshell_parser.h"
#include "stddef.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int user_prompt(char* command)
{
    //print prompt for user
    printf("my_shell$");
    fflush(NULL);
    
    //get input from user
    if (!fgets(command, MAX_LINE_LENGTH, stdin))
    {
        return 0; //if user enters EOF
    }
    else
    {
        return 1;
    }
}

void execute_command(struct pipeline *pipe_line)
{
    struct pipeline_command *commands = pipe_line->commands;
    bool background = pipe_line->is_background;
    
    //loop through each command in the pipeline
    while(commands->next != NULL)
    {
        
    }
}
void run_shell()
{
    char command[MAX_LINE_LENGTH]; //stores command
    struct pipeline *pipe_line; //command parsed
    
    //get user input until CTRL+D is entered
    while(user_prompt(command))
    {
        pipe_line = pipeline_build(command); //parse command entered
        
        execute_command(pipe_line);
        
        free(pipe_line); //free memory when done using pipeline
    }
}

int main()
{
    run_shell();
    return 0;
}