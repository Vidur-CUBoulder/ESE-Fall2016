FILE=./targets
TARGETS=`cat $(FILE)`

CC=gcc
CFLAGS=-Wall -std=c99 -g -O0
LDFLAGS=-lm
SOURCES=data.c
OBJECTS=$(SOURCE:.c=.o)
EXE_FILE=data

#General Compilation to obtain an exec.
data: $(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXE_FILE)

.PHONY=$(TARGETS)

#Target Specific Flags
PREPROCESS_FLAGS= -E
preprocess: $(OBJECTS)
	$(CC) $(CFLAGS) $(PREPROCESS_FLAGS) $(SOURCES) -o data.o

ASM_FLAGS= -S
asm-file: $(OBJECTS)
	$(CC) $(CFLAGS) $(ASM_FLAGS) $(SOURCES) -o data.s

