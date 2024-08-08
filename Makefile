
CC = gcc
FLAGS = -ansi -Wall -pedantic
GLOBAL_DEPS = globals.h utils.h
OBJS = assembler.o macro.o utils.o
TARGET = assembler
FILES = files/*.am

all:$(TARGET)

######	EXE  ######
$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJS)

assembler.o: assembler.c macro.h $(GLOBAL_DEPS)
	$(CC) $(FLAGS) -c assembler.c

macro.o: macro.c macro.h $(GLOBAL_DEPS)
	$(CC) $(FLAGS) -c macro.c

utils.o: utils.c $(GLOBAL_DEPS)
	$(CC) $(FLAGS) -c utils.c

clean:
	rm -rf *.o $(TARGET) $(FILES)

