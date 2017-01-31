########################################################################### 
# Makefile adapted from : http://gl.developpez.com/tutoriel/outil/makefile/ 
# this makefile compiles every .cpp file into .o, then link them. 
# the .cpp should be in the same folders as this Makefile. 
# (No, I don't know how to go recursive. Screw you.) 
########################################################################### 

## USELESS COMMENT
 
CC=g++ 
CFLAGS=-W -Wall -ansi -pedantic -g 
LDFLAGS= 
EXEC=testsuite 
SRC= $(wildcard *.cpp) 
OBJ= $(SRC:.c=.o) 
 
all: $(EXEC) 
 
testsuite: $(OBJ) 
  @$(CC) -o $@ $^ $(LDFLAGS) 
 
%.o: %.cpp 
  @$(CC) -o $@ -c $< $(CFLAGS) 
 
 
.PHONY: clean mrproper 
 
clean: 
  @rm -rf *.o 
 
mrproper: clean 
  @rm -rf $(EXEC) 
