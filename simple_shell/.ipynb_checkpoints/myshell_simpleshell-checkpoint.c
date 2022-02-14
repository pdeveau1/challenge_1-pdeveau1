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
