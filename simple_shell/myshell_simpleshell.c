#include "myshell_simpleshell.h"
#include "myshell_parser.h"
#include "stddef.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
    char path[MAX_LINE_LENGTH];
    //char *envp[] = {(char*) "PATH=/bin", 0};
     //Given in class slides
    if(pid == -1) //process failed
    {
        
    }
    else if(pid ==0) //parent process
    {
        //waitpid(-1, &status, 0); //wait for child to exit
        wait(NULL);
    }
    else //child process
    {
        close(0); //close stdin
        close(1); //close stdout
        strcpy(path, "/bin/");
        strcat(path, command[0]);
        //execute command
        //execve(cmd, command, envp); 
        execvp(path, command);
    }
}

void run_shell()
{
    char in_command[MAX_LINE_LENGTH];
    struct pipeline *pipe;
    
    //prompt and get input from user
    user_prompt(in_command);
    
    //run until user enters CTRL + D
    //CTRL + D returns EOF
    while(!feof(stdin))
    {
        
        //parse the command
        pipe = pipeline_build(in_command);
        //Execute the command
        execute_command(pipe->commands->command_args);
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
