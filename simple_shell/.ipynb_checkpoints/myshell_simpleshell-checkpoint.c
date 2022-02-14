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

void execute_pipeline(struct pipeline *pipe_line)
{
    struct pipeline_command *commands = pipe_line->commands;
    //bool background = pipe_line->is_background;
    int std_in, std_out;
    std_in = dup(STDIN_FILENO);
    std_out = dup(STDOUT_FILENO);
    
    
    if(commands->next == NULL) //no pipeline
    {
        int pid = fork();
        if(pid == 0) //child process
        {
            if(commands->redirect_in_path != NULL) //check if redirect to input
            {
                int in = open(commands->redirect_in_path, O_RDONLY, 0);
                dup2(in, STDIN_FILENO); //set stdin to input file
                close(in); //close input file
            }
            if(commands->redirect_out_path != NULL) //check if redirect to output
            {
                int out = open(commands->redirect_out_path, O_CREAT|O_WRONLY|O_TRUNC, 644);
                dup2(out, STDOUT_FILENO); //set stdout to output file
                close(out); //close output file
            }
            if(execvp(commands->command_args[0], commands->command_args) < 0) //error executing command
            {
                exit(1);
            }
            dup2(std_in, STDIN_FILENO);
            close(std_in);
            dup2(std_out, STDOUT_FILENO);
            close(std_out);
        }
        else
        {
            wait(NULL);
        }
    }
    else //if pipeline
    {
        //loop through each command in the pipeline
        int input = execute_command(commands, 0, 1, 0); //execute first command
        while(commands->next != NULL)
        {
            input = execute_command(commands, input, 0, 0); //execute middle commands
            commands = commands->next;
        }
        input = execute_command(commands, input, 0, 1); //execute last command
    }
    
    
}
//write to stdout, '>', 1
//read from stdin, '<', 0
int execute_command(struct pipeline_command *commands, int in_pipe, int first, int last)
{
    //char* command = commands->command_args;
    int in = in_pipe; //current file descriptor for input
    int pipe_inout[2]; //file descriptor for pipe in and out
    int pid; //id of process
    if(pipe(pipe_inout) == -1) //error piping
    {
        exit(1);
    }
    
    pid = fork(); //fork process
    
    if(pid == 0) //in child process
    {
        //execute command of pipeline
        if(first) //if first command of the pipeline
        {
            if(commands->redirect_in_path != NULL) //check if redirect to input
            {
                in = open(commands->redirect_in_path, O_RDONLY);
                dup2(in, STDIN_FILENO); //set stdin to input file
                close(in); //close input file
            }
            dup2(pipe_inout[1], STDOUT_FILENO); //process writes to next process 
        }
        else if(last) //if last command of the pipeline
        {
            if(commands->redirect_out_path != NULL) //check if redirect to output
            {
                int out = open(commands->redirect_out_path, O_WRONLY);
                dup2(out, STDOUT_FILENO); //set stdout to output file
                close(out); //close output file
            }
            dup2(in, STDIN_FILENO); //process reads from last process 
        }
        else //if a command in middle of pipeline
        {
            dup2(in, STDIN_FILENO); //process reads from last process
            dup2(pipe_inout[1], STDOUT_FILENO); //process writes to next process
        }
        
        if(execvp(commands->command_args[0], commands->command_args) < 0) //error executing command
        {
            exit(1);
        }
    }
    close(pipe_inout[1]); //no longer need to write to pipe
    if(last)
    {
        close(pipe_inout[0]); //no longer need to read from pipe
    }
    return pipe_inout[0]; //return read of pipe for next process
    
}

void run_shell()
{
    char command[MAX_LINE_LENGTH]; //stores command
    struct pipeline *pipe_line; //command parsed
    
    //get user input until CTRL+D is entered
    while(user_prompt(command))
    {
        pipe_line = pipeline_build(command); //parse command entered
        
        execute_pipeline(pipe_line);
        
        free(pipe_line); //free memory when done using pipeline
    }
}

int main()
{
    run_shell();
    return 0;
}