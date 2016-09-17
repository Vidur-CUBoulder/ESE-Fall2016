FILE:=./sources/targets
TARGETS:=$(shell cat ${FILE})

FILE:=./sources/sources_dirs.mk
DIR_INCLUDES:=$(shell cat ${FILE})

FILE:=./sources/sources_files.mk
SOURCES:=$(shell cat ${FILE})

CC:=gcc
CFLAGS:=-Wall -std=c99 -g -O0 -M -Map $(DIR_INCLUDES)
LDFLAGS:=-lm
OBJECTS:=$(SOURCES:%.c=%.o)
PRE_PROCESSED:=$(SOURCES:%.c=%.i)
EXE_FILE=executable

.PHONY=$(TARGETS)

build: $(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXE_FILE)

main.o:main/main.c
	$(CC) $(CFLAGS) -c main/main.c -o main/main.o

data.o:data/data.c
	$(CC) $(CFLAGS) -c data/data.c -o data/data.o

memory.o:memory/memory.c
	$(CC) $(CFLAGS) -c memory/memory.c -o memory/memory.o

project_1.o:project/project_1.c
	$(CC) $(CFLAGS) -c project/project_1.c -o project/project_1.o

compile-all: $(OBJECTS)
	$(CC) $(CFLAGS) -c $(SOURCES)
	@-rm -rv *.o

data.i:data/data.c
	$(CC) $(CFLAGS) -E data/data.c -o data/data.i

main.i:main/main.c
	$(CC) $(CFLAGS) -E main/main.c -o main/main.i

memory.i:memory/memory.c
	$(CC) $(CFLAGS) -E memory/memory.c -o memory/memory.i

project_1.i:project/project_1.c
	$(CC) $(CFLAGS) -E project/project_1.c -o project/project_1.i

main.S:main/main.c
	$(CC) $(CFLAGS) -S main/main.c -o main/main.S

memory.S:memory/memory.c
	$(CC) $(CFLAGS) -S memory/memory.c -o memory/memory.S

data.S:data/data.c
	$(CC) $(CFLAGS) -S data/data.c -o data/data.S

project_1.S:project/project_1.c
	$(CC) $(CFLAGS) -S project/project_1.c -o project/project_1.S


clean:
	-rm -rf $(EXE_FILE) $(OBJECTS) $(PRE_PROCESSED)



#Target Specific Flags
#PREPROCESS_FLAGS= -E
#preprocess: $(OBJECTS)
#	$(CC) $(CFLAGS) $(PREPROCESS_FLAGS) $(SOURCES) -o data.o

#ASM_FLAGS= -S
#asm-file: $(OBJECTS)
#	$(CC) $(CFLAGS) $(ASM_FLAGS) $(SOURCES) -o data.s

