# compiler to use
CC = gcc
# flags to compiler
CFLAGS = -g -Wall -O3
# include
INCLUDES = -I/include/ -Iinclude/
# source files
SRCS = src/board.c src/deck.c src/risky.c src/conf.c
# auto-generate the object files
OBJS = $(SRCS:.c=.o)
# define the executable file
MAIN = risky

all:    $(MAIN)

$(MAIN): $(OBJS) 
	        $(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS)

.c.o:
	        $(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	        $(RM) *.o *~ $(MAIN) $(OBJS)
