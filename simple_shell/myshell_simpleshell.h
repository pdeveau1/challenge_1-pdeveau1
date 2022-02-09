#ifndef MYSHELL_SIMPLESHELL_H
#define MYSHELL_SIMPLESHELL_H
#include "myshell_parser.h"
#include <stdbool.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 512
void user_prompt(char*);

void run_shell();

#endif /* MYSHELL_SIMPLESHELL_H */
