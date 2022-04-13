#ifndef FUNC_H
#define FUNC_H

#include "wordle_word.h"



// reads a file of words and converts them to wordle_words
int read_file(const STRING filename, VECTOR<wordle_word>& the_words);



// intializes our positions vector
void init_pos(VECTOR< SET<char> >& positions);



// finds the recommended words for what to play next
VECTOR<wordle_word> find_words(const VECTOR<wordle_word> possible_words, const VECTOR< SET<char> > positions, const UNOR_MAP< char, unsigned int > req_letters);



// prints the five best words that the user should choose
void best_words(VECTOR<wordle_word> rec_words);



// prunes our structures based on result from wordle
void prune_structures(const STRING result, const wordle_word temp_wordle_word, VECTOR< SET<char> >& positions, UNOR_MAP< char, unsigned int >& req_letters);



// if a letter returned gray
void gray_letter(const char letter, const unsigned int index, VECTOR< SET<char> >& positions, UNOR_MAP< char, unsigned int >& req_letters);



// if a letter returned yellow
void yellow_letter(const char letter, const unsigned int index, VECTOR< SET<char> >& positions, UNOR_MAP< char, unsigned int >& req_letters);



// if a letter returned green
void green_letter(const char letter, const unsigned int index, VECTOR< SET<char> >& positions, UNOR_MAP< char, unsigned int >& req_letters);



// partitioning for quicksort
int partition(VECTOR<double>& section, int lo, int hi);



// quicksort algorithm
void quicksort(VECTOR<double>& tobeSorted, int lo, int hi);



#endif
