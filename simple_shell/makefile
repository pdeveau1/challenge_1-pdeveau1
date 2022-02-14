override CFLAGS := -Wall -Werror -std=gnu99 -O1 -g $(CFLAGS) -I.
CC = gcc

all: myshell
    
myshell: myshell_simpleshell.o

myshell_simpleshell.o: myshell_simpleshell.c myshell_simpleshell.h myshell_parser.o
    
# Build the parser .o file
myshell_parser.o: myshell_parser.c myshell_parser.h

# Automatically discover all test files
test_c_files=$(shell find tests -type f -name '*.c')
test_o_files=$(test_c_files:.c=.o)
test_files=$(test_c_files:.c=)

# The intermediate test .o files shouldn't be auto-deleted in test runs; they
# may be useful for incremental builds while fixing fs.c bugs.
.SECONDARY: $(test_o_files)

.PHONY: clean check checkprogs

# Rules to build each individual test
tests/%: tests/%.o myshell_parser.o
	$(CC) $(LDFLAGS) $+ $(LOADLIBES) $(LDLIBS) -o $@

# Build all of the test programs
checkprogs: $(test_files)

# Run the test programs
check: checkprogs
	tests/run_tests.sh $(test_files)
    
clean:
	rm -f *.o $(test_files) $(test_o_files)
