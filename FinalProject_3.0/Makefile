# Author: Beta Structures
# E-mail: matt.morrison@nd.edu
# File name: Makefile
# Date created: 4/14/22
# File contents: the makefile for final project

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
# Command: make solver

$(OBJ)/word_funcs.o: $(SRC)/word_funcs.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@
	
$(OBJ)/solver.o: $(SRC)/solver.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

objects :=  $(OBJ)/solver.o $(OBJ)/word_funcs.o

solver: $(initialize) $(objects)
	$(CC) $(CXXFLAGS) -o $(EXE)/$@ $(objects)
	

# Make clean
clean:
	rm -rf $(OBJ)/* $(EXE)/*
