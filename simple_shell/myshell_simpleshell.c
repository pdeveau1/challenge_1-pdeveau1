#include "myshell_simpleshell.h"
#include "myshell_parser.h"
#include "stddef.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void user_prompt(char *in_command)
{
    printf("my_shell$");
    fgets(in_command, MAX_LINE_LENGTH, stdin);
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
        
        
        
        
        
        pipeline_free(pipe);
    }while(!feof(stdin));
    
    printf("\n");
}

int main()
{
    run_shell();
}