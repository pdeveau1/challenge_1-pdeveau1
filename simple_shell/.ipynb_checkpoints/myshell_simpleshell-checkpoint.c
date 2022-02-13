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
    ignore_ret(fgets(in_command, MAX_LINE_LENGTH, stdin));
}

void execute_command(struct pipeline_command * commands)
{
    pid_t pid = fork(); //return value: -1 = failed, 0 = in child process, positive = in parent process
    int status;
    
    
    if (pid == 0) 
    {
        int in = execute_redirect_in(commands->redirect_in_path);
        int out = execute_redirect_out(commands->redirect_out_path);
        if (execvp(commands->command_args[0], commands->command_args) < 0)
        {
          printf("dash: command not found: %s\n", commands->command_args[0]);
        }
        reset_inout(in, out);
        //after execution, revert back to stdin and stdout
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        printf(RED "Error forking" RESET "\n");
    }
    else 
    {
        //waitpid(pid, & status, WUNTRACED);
        wait(&pid);
    }
}

int execute_redirect_in(char* inpath)
{
    int tmp = dup(0);
    int in;
    if(inpath)
    {
        in = open(inpath, O_RDONLY); //open input file
    }
    else
    {
        in = dup(tmp); //duplicate stdin for input file
    }
    dup2(in,0);
    close(in);
    return tmp;
}

int execute_redirect_out(char* outpath)
{
    int tmp = dup(1);
    int out;
    if(outpath)
    {
        out = open(outpath,O_WRONLY);
    }
    else
    {
        out = dup(tmp);
    }
    dup2(out,1);
    close(out);
    return tmp;
}

void reset_inout(int in, int out)
{
    dup2(in, 0);
    dup2(out, 1);
    close(in);
    close(out);
}

void run_shell()
{
    char in_command[MAX_LINE_LENGTH];
    struct pipeline *pipe;
    
    //prompt and get input from user
    user_prompt(in_command);
    
    //run until user enters CTRL + D
    //CTRL + D returns EOF
    while(in_command != NULL)
    {
        
        //parse the command
        pipe = pipeline_build(in_command);
        
        //Execute the command
        execute_command(pipe->commands);
        
        //free memory for pipe
        pipeline_free(pipe);
        
        //prompt and get input from user
        user_prompt(in_command);
    }
    
    printf("\n");
}


int main()
{
    run_shell();
}
