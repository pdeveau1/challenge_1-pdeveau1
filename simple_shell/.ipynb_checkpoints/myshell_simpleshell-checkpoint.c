#include "myshell_simpleshell.h"
#include "myshell_parser.h"
#include "stddef.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* user_prompt()
{
    char in_command[MAX_LINE_LENGTH];
    printf("my_shell$");
    gets(in_command);
}