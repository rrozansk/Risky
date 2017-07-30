# compiler to use gcc, clang, g++, etc.
CC = gcc
# compiler flags (add -g for debug)
CFLAGS = -Wall -O3
# includes (header file locations)
INCLUDES = -I/include/ -Iinclude/
# all the files to include in the generated .tar
TAR_FILES = include/*.h src/*.c test/*.c LICENSE.txt Makefile README.md conf.ini
# risky executable
MAIN_DEPS = include/ini.h src/ini.c \
            include/log.h src/log.c \
            include/dna.h src/dna.c \
            include/risk.h src/risk.c \
            src/main.c
MAIN_OBJS = $(MAIN_DEPS:.c=.o)
MAIN = risky
# log library test executable
LOG_DEPS = include/log.h src/log.c test/testLOG.c
LOG_OBJS = $(LOG_DEPS:.c=.o)
LOG_TEST = logtest
# ini library test executable
INI_DEPS = include/ini.h src/ini.c test/testINI.c
INI_OBJS = $(INI_DEPS:.c=.o)
INI_TEST = initest
# dna library test executable
DNA_DEPS = include/dna.h src/dna.c test/testDNA.c
DNA_OBJS = $(DNA_DEPS:.c=.o)
DNA_TEST = dnatest
# risk library test executable
RISK_DEPS = include/risk.h src/risk.c test/testRISK.c
RISK_OBJS = $(RISK_DEPS:.c=.o)
RISK_TEST = risktest

# targets not dependent on files so make doesnt get confused
.PHONY:  default build rebuild all install clean tar tests

default: $(MAIN)

build:   $(MAIN)

rebuild: clean build

all:     $(MAIN)

$(MAIN): $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(MAIN_OBJS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

install:  rebuild
	\cp $(MAIN) /usr/bin/

clean:
	\rm -f *.o *~ src/*.o src/*~ test/*.o test/*~ $(MAIN) $(DNA_TEST) $(INI_TEST) $(RISK_TEST) $(LOG_TEST)

tar:
	\tar -cvf $(MAIN).tar $(TAR_FILES)

tests: $(DNA_TEST) $(INI_TEST) $(RISK_TEST) $(LOG_TEST)

$(DNA_TEST): $(DNA_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(DNA_TEST) $(DNA_OBJS)
	./$(DNA_TEST)
	\rm -f *.o *~ src/*.o src/*~ test/*.o test/*~ $(DNA_TEST)

$(INI_TEST): $(INI_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(INI_TEST) $(INI_OBJS)
	./$(INI_TEST)
	\rm -f *.o *~ src/*.o src/*~ test/*.o test/*~ $(INI_TEST)

$(RISK_TEST): $(RISK_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(RISK_TEST) $(RISK_OBJS)
	./$(RISK_TEST)
	\rm -f *.o *~ src/*.o src/*~ test/*.o test/*~ $(RISK_TEST)

$(LOG_TEST): $(LOG_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(LOG_TEST) $(LOG_OBJS)
	./$(LOG_TEST)
	\rm -f *.o *~ src/*.o src/*~ test/*.o test/*~ $(LOG_TEST)
