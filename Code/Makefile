# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g
# -Wall

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lpthread

default: graph
# To create the executable file count we need the object files
# grepfile.o timer.o
graph: grepfile.o main.o spanningTree.o server.o client.o
	$(CC) $(CFLAGS) -o graph main.o grepfile.o spanningTree.o server.o client.o $(LIBS)
# the build target executable
main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LIBS)

grepfile.o:   grepfile.c
	$(CC) $(CFLAGS) -c grepfile.c

spanningTree.o: spanningTree.c
	$(CC) $(CFLAGS) -c spanningTree.c

server.o: server.c 
	$(CC) $(CFLAGS) -c server.c

client.o: client.c 
	$(CC) $(CFLAGS) -c client.c

clean:
	$(RM) graph *.o *~
