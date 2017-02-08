########################################################################### 
# Makefile adapted from : http://gl.developpez.com/tutoriel/outil/makefile/ 
# this makefile compiles every .cpp file into .o, then link them. 
# the .cpp should be in the same folders as this Makefile. 
# (No, I don't know how to go recursive. Screw you.) 
########################################################################### 
 
CC=g++
CFLAGS=-std=c++11 -W -Wall -ansi -pedantic
LDFLAGS=
EXEC=testsuite
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
