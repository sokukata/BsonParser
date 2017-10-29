CC=g++
CFLAGS= -std=c++14 -pedantic -Wall -Wextra -Werror -g
BIN=besonParser
OBJNAME= main.o

OBJ=$(addprefix src/, $(OBJNAME))

all : besonParser

besonParser: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ)
	$(RM) $(BIN)

