override CFLAGS := -Wall -Werror -std=gnu99 -O1 -g $(CFLAGS) -I.
CC = gcc

all: myshell
    
myshell: myshell_simpleshell.c myshell_simpleshell.h myshell_parser.c myshell_parser.h
	$(CC) $(CFLAGS) myshell_simpleshell.c myshell_parser.c -o myshell


clean:
	rm -f *~ *.o myshell
