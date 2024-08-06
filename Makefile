
CC = gcc
FLAGS = -ansi -Wall -pedantic
GLOBAL_DEPS = globals.h utils.h
OBJS = macroDeploy.o macro.o utils.o
TARGET = assembler

all:$(TARGET)

######	EXE  ######
$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJS)

macroDeploy.o: macroDeploy.c macro.h $(GLOBAL_DEPS)
	$(CC) $(FLAGS) -c macroDeploy.c

macro.o: macro.c macro.h $(GLOBAL_DEPS)
	$(CC) $(FLAGS) -c macro.c

utils.o: utils.c utils.h
	$(CC) $(FLAGS) -c utils.c

clean:
	rm -rf *.o

