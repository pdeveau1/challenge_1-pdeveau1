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

#define TOK_DELIM " \t\r\n"
#define RED "\033[0;31m"
#define RESET "\e[0m"

//https://stackoverflow.com/questions/7271939/warning-ignoring-return-value-of-scanf-declared-with-attribute-warn-unused-r/13390863
static inline void ignore_ret() {}

void user_prompt(char *in_command)
{
    printf("my_shell$");
    if(feof(stdin))
    {
        _Exit(0);
    }
    ignore_ret(fgets(in_command, MAX_LINE_LENGTH, stdin));
}

void execute_command(struct pipeline_command *command)
{
    int status;
    pid_t pid = fork();
    if(pid == 0)
    {
        int std_in = execute_redirect_in(command->redirect_in_path);
        int std_out = execute_redirect_out(command->redirect_out_path);
        if(execvp(command->command_args[0], command->command_args) < 0) 
        {     
            printf("*** ERROR: exec failed\n");
            exit(1);
        }
        dup2(std_in,0);
        close(std_in);
        dup2(std_out,1);
        close(std_out);
    }
    else if(pid < 0)
    {
        printf("Failed to fork\n");
        //exit(1);
    }
    else
    {
        waitpid(pid, &status, 0);
        //exit(status);
    }
}

int execute_redirect_in(char* in_path)
{
    int in;
    int std_in = dup(0);
    if(in_path)
    {
        in = open(in_path,O_RDONLY, 0);
        dup2(in, 0);
        close(in);
    }
    return std_in;
}

int execute_redirect_out(char* out_path)
{
    int out;
    int std_out = dup(1);
    if(out_path)
    {
        out = open(out_path,O_CREAT|O_WRONLY|O_TRUNC, 644);
        dup2(out,1);
        close(out);
    }
    return std_out;
}

void run_shell()
{
    char in_command[MAX_LINE_LENGTH];
    struct pipeline *pipe;
    
    //prompt and get input from user
    user_prompt(in_command);
    
    //run until user enters CTRL + D
    //CTRL + D returns EOF
    while(1)
    {
        
        //parse the command
        pipe = pipeline_build(in_command);
        
        //Execute the command
        execute_command(pipe->commands);
        
        //free memory for pipe
        pipeline_free(pipe);
        
        //prompt and get input from user
        user_prompt(in_command);
        //exit(in_command == NULL);
    }
}


int main()
{
    run_shell();
}