/******************************
 * Team: Beta Structures
 * Names: Danielle Croft, Hannah Long, Kate Mealey, Kelly Williams
 * Emails: dcroft@nd.edu, hlong3@nd.edu, kmealey2@nd.edu, kwilli29@nd.edu
 * File Name: word_funcs.h
 * Date Created: 04/14/2022
 * File Contents: This file contains the function definitions
 * 	for a wordle solver
 *****************************/

#ifndef WORD_FUNCS_H
#define WORD_FUNCS_H

#include "Word.h"

// used to information about each letter at each position in UNOR_MAP letters
// in wordle, gray means a letter is not in the solution word
// 			  yellow means a letter is in the solution word, but not in the guessed place
// 			  green means the letter is in the solution word at the guessed place
typedef enum {
	NAN,
	GRAY,
	YELLOW,
	GREEN
} Color;

// function headers:

// the three functions used for quicksort
// "by_info" is true if the words are being sorted by the amount of information they give, and false if they're being sorted by their commonality
void swap(VECTOR<Word>& words, int i, int j);
int partition(VECTOR<Word>& section, int lo, int hi, bool by_info);
void quicksort(VECTOR<Word>& tobeSorted, int lo, int hi, bool by_info);

// initializing the letter map
int init_letter_map( UNOR_MAP< char, VECTOR<Color> >& letter_map );

// reading a file and putting the words into a vector
int read_file(VECTOR<Word>& the_words);

// prints a welcome screen
void welcome();

// gets an input word from the user
int get_word(STRING &word, const VECTOR<Word> &words);

// gets the color result from the user
int get_colors(STRING &colors);

// updates the letter map based on the results the user got
int update_letter_map(STRING word, STRING colors, UNOR_MAP<char, VECTOR<Color> > &letter_map);

// finds the words that are valid for the user to enter into wordle
VECTOR<Word> find_words(const UNOR_MAP< char, VECTOR<Color> > letter_map, VECTOR<Word>& the_words);\

// displays the words to the user in a ranked order
int display_words(VECTOR<Word>& the_words, int num_tries);

#endif
