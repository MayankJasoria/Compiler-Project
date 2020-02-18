# set the compiler
CC=gcc

# set compiler flags
CFLAGS=-c

#set dependencies for the program
DEPS_PROG=driver.o

# TODO: Complete the compilation dependencies etc..
driver: $(DEPS_PROG)
	$(CC) -o erplag $(DEPS_PROG)

clean:
	rm -rf *.o

cleanAll:
	rm -rf *.o *.out *.exe