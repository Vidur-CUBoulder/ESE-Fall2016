FILE:=./sources/targets
TARGETS:=$(shell cat ${FILE})

FILE:=./sources/sources_dirs.mk
DIR_INCLUDES:=$(shell cat ${FILE})

FILE:=./sources/sources_files.mk
SOURCES:=$(shell cat ${FILE})

CC=gcc
#DIR_INCLUDES=-I./data -I./headers -I./memory -I./project -I./main
CFLAGS=-Wall -std=c99 -g -v -O0 $(DIR_INCLUDES)
LDFLAGS=-lm
#SOURCES=data/data.c memory/memory.c project/project_1.c main/main.c
OBJECTS=$(SOURCES:.c=.o)
HEADERS=$(SOURCES:.c=.h)
EXE_FILE=executable

.PHONY=$(TARGETS)

#General Compilation to obtain an exec.
build: $(HEADERS) $(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXE_FILE)


#Target Specific Flags
#PREPROCESS_FLAGS= -E
#preprocess: $(OBJECTS)
#	$(CC) $(CFLAGS) $(PREPROCESS_FLAGS) $(SOURCES) -o data.o

#ASM_FLAGS= -S
#asm-file: $(OBJECTS)
#	$(CC) $(CFLAGS) $(ASM_FLAGS) $(SOURCES) -o data.s

