#include "myshell_parser.h"
#include "stddef.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//https://stackoverflow.com/questions/656542/trim-a-string-in-c
void trim (char *s)
{
    int i;

    // skip left side white spaces
    while (isspace (*s))
    {
        s++;  
    }
    // skip right side white spaces
    for (i = strlen (s) - 1; (isspace (s[i])); i--); 
    s[i + 1] = '\0';
    //printf (";%s;\n", s);
}

//https://www.programmingsimplified.com/c/source-code/c-substring
char *substring(char *string, int position, int length)
{
   char *p;
   int c;
 
   p = malloc(length+1);
   
   if (p == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(1);
   }
 
   for (c = 0; c < length; c++)
   {
      *(p+c) = *(string+position);      
      string++;  
   }
 
   *(p+c) = '\0';
 
   return p;
}

//creates the structure for the next pipeline command
struct pipeline_command *create_pipeline_command()
{
    struct pipeline_command *commands = (struct pipeline_command*)malloc(sizeof(struct pipeline_command));
    (commands)->redirect_out_path = NULL;
    (commands)->redirect_in_path = NULL;
    (commands)->command_args[0] = NULL;
    (commands)->next = NULL;
    return commands;
}

/*
This function creates a pipeline structure that represents the given command line. You may or may not choose to use malloc() while implementing this function. If you choose to use malloc(), any allocated memory must be freed by pipeline_free().
*/
struct pipeline *pipeline_build(const char *command_line)
{
    //lexing: when lexing, you group parts of your string into a series of tokens  
    
    int lineLength = strlen(command_line); //gets length of command_line
    char *tokens[lineLength]; //will store the tokens of the command_line
    char line1[lineLength]; //new line to search tokens for after it is split
    char *line = line1;
    strcpy(line, command_line);
    trim(line);
    //char new_line[lineLength];
    //char tok[2];
    int tokenCount = 0;
    int i = 0;
    
    while(i < strlen(line))
    {
        //separation for symbols
        if(line[i] == '&' || line[i] == '|' || line[i] == '<' || line[i] == '>')
        {
            if(i != 0)
            {
                //memset(new_line, '\0', sizeof(new_line));
                //strncpy(new_line, line, i);
                //trim(new_line);
                //memset(tokens[tokenCount], '\0', sizeof(new_line));
                tokens[tokenCount] = substring(line, 0, i);
                tokenCount++;
            }
            
            line = line + i;
            tokens[tokenCount] = substring(line, 0, 1);
            
            tokenCount++;
            line = line + 1;
            trim(line);
            i = 0;
        }
        //separation for white space
        else if(isspace(line[i]))
        {
            if((i != 0))
            {
                //memset(new_line, '\0', sizeof(new_line));
                //strncpy(new_line, line, i);
                //trim(new_line);
                //memset(tokens[tokenCount], '\0', sizeof(new_line));
                tokens[tokenCount] = substring(line, 0, i);
                tokenCount++;
            }
                line = line + i + 1;
                trim(line);
                i = 0;
        }
        else
        {
            i++;
        }
    }
    if(!isspace(line[i]) && strcmp(line,"") != 0)
    {
        //memset(new_line, '\0', sizeof(new_line));
                //strncpy(new_line, line, i);
                //trim(new_line);
                //memset(tokens[tokenCount], '\0', sizeof(new_line));
                tokens[tokenCount] = substring(line, 0, i);
    }
    else
    {
        tokenCount--;
    }
    
    //parsing: when parsing, you search for patterns of tokens that match an expected structure of symbols
    //creation of pipe
    struct pipeline *pipe = (struct pipeline*)malloc(sizeof(struct pipeline));
    pipe->is_background = false;
    if((strcmp(tokens[tokenCount], "&") == 0))
    {
        pipe->is_background = true;
    }
    //pipe->commands = create_pipeline_command();
    struct pipeline_command *commands = create_pipeline_command();
    struct pipeline_command *commands_head = commands;
    int commandCount = 0;
    for(int i = 0; i <= tokenCount; i++)
    {
        //printf("token: %s\n", tokens[])
        //check for redirect in
        if(strcmp(tokens[i], "<") == 0)
        {
            commands->redirect_in_path = tokens[i + 1];
            //free(tokens[i]);
            //free(tokens[i + 1]);
            //commands->redirect_out_path = NULL;
            i++;
        }
        //check for redirect out
        else if(strcmp(tokens[i], ">") == 0)
        {
            commands->redirect_out_path = tokens[i + 1];
            //free(tokens[i]);
            //free(tokens[i + 1]);
            //commands->redirect_in_path = NULL;
            i++;
        }
        //check for pipe
        else if(strcmp(tokens[i], "|") == 0)
        {
            commands->next = create_pipeline_command();
            commands = commands->next;
            commandCount = 0;
            //free(tokens[i]);
        }
        else if((strcmp(tokens[i], "&") == 0))
        {
            pipe->is_background = true;
        }
        else
        {
            commands->command_args[commandCount] = tokens[i];
            commandCount++;
            commands->command_args[commandCount] = NULL;
            //free(tokens[i]);
        }
    }
    
	// TODO: Implement this function
    pipe->commands = commands_head;
	return pipe;
}


/*
Frees a given pipeline that was created with pipeline_build(). If your pipeline_build() function performs any dynamic memory allocation, this is where the corresponding deallocation must occur for pipeline and for any nested data structures it contains.
*/
void pipeline_free(struct pipeline *pipeline)
{
	free(pipeline->commands);
    free(pipeline);
}

/*int main()
{
    char command_line[] = "a& \n";
    pipeline_build(command_line);
    return(0);
}*/

