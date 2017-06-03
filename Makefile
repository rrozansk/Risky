# compiler to use
CC = gcc
# remove cmd
RM = rm -f
# flags to compiler (add -g for debug)
CFLAGS = -Wall -O3
# include
INCLUDES = -I/include/ -Iinclude/
# all the files to include in the .tar
TAR_FILES = include/*.h src/*.c test/*.c LICENSE.txt Makefile README.md conf.ini
# source files
SRCS = src/ini.c src/log.c src/dna.c src/risk.c src/main.c
# auto-generate the object files
OBJS = $(SRCS:.c=.o)
# define the executable file
MAIN = risky
# testing log library
LOG_TEST_DEPS = src/log.c test/testLOG.c
LOG_OBJS = $(LOG_TEST_DEPS:.c=.o)
LOG_TEST = logtest
# testing ini library
INI_TEST_DEPS = src/ini.c test/testINI.c
INI_OBJS = $(INI_TEST_DEPS:.c=.o)
INI_TEST = initest
# testing dna library
DNA_TEST_DEPS = src/dna.c test/testDNA.c
DNA_OBJS = $(DNA_TEST_DEPS:.c=.o)
DNA_TEST = dnatest
# testing risk library
RISK_TEST_DEPS = src/risk.c test/testRISK.c
RISK_OBJS = $(RISK_TEST_DEPS:.c=.o)
RISK_TEST = risktest

# target not dependent on files so make doesnt get confused
.PHONY:  default build rebuild all install clean tar tests

default: $(MAIN)

build:   $(MAIN)

rebuild: clean build

all:     $(MAIN)

$(MAIN): $(OBJS)
	        $(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS)

.c.o:
	      	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

install:
					cp $(MAIN) /usr/bin

clean:
	        $(RM) *.o *~ $(MAIN) $(OBJS) $(DNA_TEST) $(DNA_OBJS) $(INI_TEST) $(INI_OBJS) $(RISK_TEST) $(RISK_OBJS) $(LOG_TEST) $(LOG_OBJS)

tar:
					tar -cvf $(MAIN).tar $(TAR_FILES)

tests: dnatest initest risktest logtest

dnatest: $(DNA_OBJS)
					$(CC) $(CFLAGS) $(INCLUDES) -o $(DNA_TEST) $(DNA_OBJS)

initest: $(INI_OBJS)
					$(CC) $(CFLAGS) $(INCLUDES) -o $(INI_TEST) $(INI_OBJS)

risktest: $(RISK_OBJS)
					$(CC) $(CFLAGS) $(INCLUDES) -o $(RISK_TEST) $(RISK_OBJS)

logtest: $(LOG_OBJS)
					$(CC) $(CFLAGS) $(INCLUDES) -o $(LOG_TEST) $(LOG_OBJS)
