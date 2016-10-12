#Extracting information from various files and
#storing them in variables

FILE:=./sources/targets
TARGETS:=$(shell cat ${FILE})

FILE:=./sources/sources_dirs.mk
DIR_INCLUDES:=$(shell cat ${FILE})

FILE:=./sources/sources_files.mk
SOURCES:=$(shell cat ${FILE})

#Get the architecture type as a variable passed
#from the command line interface. If no variable
#is passed, assume the default to be host

#Input Var. to the compile time switch.
#COMPILETIME_SWITCH:=COMPILE_PROJECT_1

#Input Var. to define the architecture
ARCH:=

#Input Var. for the object-dump target
INPUT:=

ifndef ARCH
ARCH:=host
endif

#_x86_64 Specific Flags and Variables
ifeq ($(ARCH),host) 
CC:=gcc
CFLAGS:=-Wall -std=c99 -g -O0 $(DIR_INCLUDES)
ARCHIVER:=ar
OBJ_DUMP:=objdump
SIZE:=size
endif

#BeagleBone Black Specific Flags and Variables
ifeq ($(ARCH),bbb) 
CC:=arm-linux-gnueabihf-gcc
CFLAGS:=-Wall -std=c99 -g -O0 $(DIR_INCLUDES)
ARCHIVER:=arm-linux-gnueabihf-ar
OBJ_DUMP:=arm-linux-gnueabihf-objdump
SIZE:=arm-linux-gnueabihf-size
endif

#Freedom Freescale Specific Flags and Variables
ifeq ($(ARCH),frdm)
CC:=arm-none-eabi-gcc
CFLAGS:=-Wall -std=c99 -g -mthumb -O0 --specs=nosys.specs $(DIR_INCLUDES)
ARCHIVER:=arm-linux-gnueabihf-ar
OBJ_DUMP:=arm-none-eabi-objdump
SIZE:=arm-none-eabi-size
endif

#Compiler/Linker Specific Options & Generated Files
MAP_FILE:=mapout.map
EXE_FILE=project
AR_FILE:=./libproject1.a
OBJDUMP_FILE:=objdump_file

MAP_FLAGS:=-Wl,-Map,$(MAP_FILE) 
HEADERS:=$(SOURCES:%.c=%.h)
OBJECTS:=$(SOURCES:%.c=%.o)
PRE_PROCESSED:=$(SOURCES:%.c=%.i)
ASM_FILES:=$(SOURCES:%.c=%.S)

.PHONY=$(TARGETS)

build: $(OBJECTS) $(SOURCES)
	#$(CC) $(CFLAGS) -D$(COMPILETIME_SWITCH) $(MAP_FLAGS) $(SOURCES) -o $(EXE_FILE)
	$(CC) $(CFLAGS) $(MAP_FLAGS) $(SOURCES) -o $(EXE_FILE)
	$(SIZE) ./$(EXE_FILE)

object-dump: $(OBJECTS) $(SOURCES)
	$(OBJ_DUMP) -fhstg $(INPUT) > $(OBJDUMP_FILE)

upload:$(OBJECTS)
	./upload.sh

build-lib:memory.o data.o
	$(ARCHIVER) rcs $(AR_FILE) memory/memory.o data/data.o
	@chmod 776 $(AR_FILE)
	@file $(AR_FILE)

preprocess: memory.i project_1.i data.i main.i

asm-file: memory.S project_1.S data.S main.S

compile-all: preprocess asm-file objects

objects:$(SOURCES) $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES)
	@rm -r ./a.out

main.o:main/main.c
	$(CC) $(CFLAGS) -c main/main.c -o main/main.o

data.o:data/data.c
	$(CC) $(CFLAGS) -c data/data.c -o data/data.o

memory.o:memory/memory.c
	$(CC) $(CFLAGS) -c memory/memory.c -o memory/memory.o

project_1.o:project_1/project_1.c
	$(CC) $(CFLAGS) -c project_1/project_1.c -o project_1/project_1.o

data.i:data/data.c
	$(CC) $(CFLAGS) -E data/data.c -o data/data.i

main.i:main/main.c
	$(CC) $(CFLAGS) -E main/main.c -o main/main.i

memory.i:memory/memory.c
	$(CC) $(CFLAGS) -E memory/memory.c -o memory/memory.i

project_1.i:project_1/project_1.c
	$(CC) $(CFLAGS) -E project_1/project_1.c -o project_1/project_1.i

main.S:main/main.c
	$(CC) $(CFLAGS) -S main/main.c -o main/main.S

memory.S:memory/memory.c
	$(CC) $(CFLAGS) -S memory/memory.c -o memory/memory.S

data.S:data/data.c
	$(CC) $(CFLAGS) -S data/data.c -o data/data.S

project_1.S:project_1/project_1.c
	$(CC) $(CFLAGS) -S project_1/project_1.c -o project_1/project_1.S

clean:
	-rm -rf $(EXE_FILE) $(OBJECTS) $(AR_FILE) $(OBJDUMP_FILE) $(MAP_FILE) $(PRE_PROCESSED) $(ASM_FILES)
