# set the compiler
CC=gcc

# set compiler flags
CFLAGS=-c

#set dependencies for the program
DEPS_PROG=driver.o

parser: parser.c
	cls
	$(CC) -g -o a parser.c parserTest.c lexer.c data_structures/stack.c data_structures/linked_list.c data_structures/hash_map.c

# TODO: Complete the compilation dependencies etc..
driver: $(DEPS_PROG)
	$(CC) -o erplag $(DEPS_PROG)

clean:
	rm -rf *.o

cleanAll:
	rm -rf *.o *.out *.exe