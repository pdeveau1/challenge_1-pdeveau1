#include "myshell_simpleshell.h"
#include "myshell_parser.h"
#include "stddef.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

//https://stackoverflow.com/questions/7271939/warning-ignoring-return-value-of-scanf-declared-with-attribute-warn-unused-r/13390863
static inline void ignore_ret() {}

void user_prompt(char *in_command)
{
    printf("my_shell$");
    ignore_ret(fgets(in_command, MAX_LINE_LENGTH, stdin));
}

void execute_command(char** command)
{
    pid_t pid = fork(); //return value: -1 = failed, 0 = in child process, positive = in parent process
     //Given in class slides
    if(pid == -1) //process failed
    {
        
    }
    else if(pid ==0) //parent process
    {
        //waitpid(-1, &status, 0); //wait for child to exit
    }
    else //child process
    {
        execve(command[0], command, 0); //execute command
    }
}

void run_shell()
{
    char in_command[MAX_LINE_LENGTH];
    struct pipeline *pipe;
    //run until user enters CTRL + D
    //CTRL + D returns EOF
    do
    {
        //prompt and get input from user
        user_prompt(in_command);
        //parse the command
        pipe = pipeline_build(in_command);
        //Execute the command
        execute_command(pipe->commands->command_args);
       
        
        
        
        pipeline_free(pipe);
    }while(!feof(stdin));
    
    printf("\n");
}


int main()
{
    run_shell();
}
