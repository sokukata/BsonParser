CC=g++
CFLAGS= -std=c++14 -pedantic -Wall -Wextra -Werror -g
BIN=bsonParser
OBJNAME= main.o bson.o element.o

OBJ=$(addprefix src/, $(OBJNAME))

all : bsonParser

bsonParser: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ)
	$(RM) $(BIN)

