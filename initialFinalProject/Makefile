# Author: Danielle Croft
# E-mail: matt.morrison@nd.edu
# File name: Makefile
# Date created: 3/22/22
# File contents: the makefile for PC07

# g++ is for the GCC compiler for C++
CC := g++

# CFLAGS are the compiler flages for when we compile C code in this course
# FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -Werror -lm
FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -lm
CXXFLAGS := -m64 -std=c++11 $(FLAGS)

# Folder Variables
INC := include
SRC := src
OBJ := objects
EXE := exe

# Make initialize - Create the objects and executables

initialize:
	rm -rf $(OBJ) $(EXE)
	mkdir $(OBJ) $(EXE)


# Run Compilation Command
# Command: make proj

$(OBJ)/func.o: $(SRC)/func.cpp
	$(CC) $(CXXFLAGS) -c $(SRC)/func.cpp -o $@
	
$(OBJ)/proj.o: $(SRC)/proj.cpp
	$(CC) $(CXXFLAGS) -c $(SRC)/proj.cpp -o $@

projObjs :=  $(OBJ)/proj.o $(OBJ)/func.o

proj: $(initialize) $(projObjs)
	$(CC) $(CXXFLAGS) -o $(EXE)/proj $(projObjs)
	

# Make clean
clean:
	rm -rf $(OBJ)/* $(EXE)/*
