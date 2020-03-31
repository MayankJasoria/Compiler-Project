# GROUP 48
# PUNEET ANAND		2016B4A70487P
# MAYANK JASORIA	2016B1A70703P
# SHUBHAM TIWARI	2016B4A70945P
# VIBHAV OSWAL		2016B4A70594P

# -- Detect OS for AST compilation --
ifeq ($(OS),Windows_NT)
	# Windows 
	DS=data_structures\stack.c data_structures\linked_list.c data_structures\n_ary_tree.c data_structures\ast.c 
	GDB_AUTO=gdb --batch --command=debug.gdb --args ast
else
	# Linux
	DS=data_structures/stack.c data_structures/linked_list.c data_structures/n_ary_tree.c data_structures/ast.c 
	GDB_AUTO=gdb --batch --command=debug.gdb --args ./ast
endif
#-----------------------------------

# set the compiler
CC=gcc

# set compiler flags
CFLAGS=-g -o

#set dependencies for the program
DEPS_PROG=driver.c parser.c lexer.c data_structures/stack.c data_structures/linked_list.c data_structures/n_ary_tree.c

#set executable name
OUT_NAME=stage1exe

# TODO: Complete the compilation dependencies etc..
driver: $(DEPS_PROG)
	$(CC) $(CFLAGS) $(OUT_NAME) $(DEPS_PROG)

ast: ast_test.c
	$(CC) $(CFLAGS) ast ast_test.c parser.c lexer.c $(DS)  

ast_debug: ast_test.c
	$(CC) $(CFLAGS) ast ast_test.c parser.c lexer.c $(DS)  
	$(GDB_AUTO)


parser: parserTest.c
	cls
	$(CC) $(CFLAGS) a parser.c parserTest.c lexer.c data_structures\stack.c data_structures\linked_list.c data_structures\n_ary_tree.c
	a

lexer: lexer.c
	$(CC) $(CFLAGS) lex main.c lexer.c

clean:
	rm -rf *.o

cleanAll:
	rm -rf *.o *.out *.exe
