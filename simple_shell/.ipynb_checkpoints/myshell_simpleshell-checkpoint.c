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
    //run until user enters CTRL + D
    //CTRL + D returns EOF
    user_prompt(in_command);
    while(in_command != 0)
    {
        user_prompt(in_command);
    }
}

int main()
{
    run_shell();
}