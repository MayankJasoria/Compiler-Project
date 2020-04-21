# GROUP 48
# PUNEET ANAND		2016B4A70487P
# MAYANK JASORIA	2016B1A70703P
# SHUBHAM TIWARI	2016B4A70945P
# VIBHAV OSWAL		2016B4A70594P

# set the compiler
CC=gcc

# set compiler flags
CFLAGS=-g -o

#set dependencies for the program
DEPS_PROG=driver.c codeGen.c parser.c lexer.c utils.c semanticAnalyzer.c typeChecker.c symbolTable.c stack.c linked_list.c n_ary_tree.c ast.c hash_map.c queue.c

#set executable name
OUT_NAME=compiler

# TODO: Complete the compilation dependencies etc..
driver: $(DEPS_PROG)
	$(CC) $(CFLAGS) $(OUT_NAME) $(DEPS_PROG)

clean:
	rm -rf *.o

cleanAll:
	rm -rf *.o *.out *.exe
