# set the compiler
CC=gcc

# set compiler flags
CFLAGS=-o

#set dependencies for the program
DEPS_PROG=driver.c parser.c lexer.c data_structures/stack.c data_structures/linked_list.c data_structures/n_ary_tree.c

#set executable name
OUT_NAME=stage1exe

# TODO: Complete the compilation dependencies etc..
driver: $(DEPS_PROG)
	$(CC) $(CFLAGS) $(OUT_NAME) $(DEPS_PROG)

parser: parser.c
	#cls
	$(CC) -g -o a parser.c parserTest.c lexer.c data_structures/stack.c data_structures/linked_list.c data_structures/n_ary_tree.c
	./a

clean:
	rm -rf *.o

cleanAll:
	rm -rf *.o *.out *.exe
