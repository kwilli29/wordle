/******************************
 * Team: Beta Structures
 * Names: Danielle Croft, Hannah Long, Kate Mealey, Kelly Williams
 * Emails: dcroft@nd.edu, hlong3@nd.edu, kmealey2@nd.edu, kwilli29@nd.edu
 * File Name: solver.cpp
 * Date Created: 04/14/2022
 * File Contents: This file contains the main function for a wordle solver
 *****************************/

#include "../include/word_funcs.h"

int main() {
	
	// starting the game
	COUT << "\033[2J\033[1;1H";
	COUT << "Booting the game..." << ENDL << ENDL;

	// initialize variables:
	int status = EXIT_SUCCESS;
	int err;
	int num_tries = 1;
	int end_game = 0;
	STRING guessed_word;
	STRING guessed_word_colors;
	STRING user_input;

	// intialize words vector
	VECTOR<Word> words;
		// this vector will be populated with Word structs for every word in info-words.txt
		// the Words struct (see include/Word.h) contains the string of the word, a ranking
		// by commonality of the word and a ranking by the commonality of the letters (called
		// the info ranking, since guessing words with letters that show up in many other words
		// will give you the most information about what other words are and are not valid)

	// initialize letter_map
	UNOR_MAP< char, VECTOR<Color> > letter_map;
	init_letter_map(letter_map);

		// letter_map is the structure we use to store criteria for a word in the word list
		// to be a valid guess.
		// letter_map is an unordered map where each word  is a key
		// The value at each letter is a static array of length 5, whose indices represent
		// each place in the wordle solution word. The value at each of these indices is
		// a Color (int enum): NAN, GRAY, YELLOW, or GREEN, and it gets updated as more
		// information is gained about the solution through the user's input after guesses.

	// load in the words from the file
	err = read_file(words);
	if (err) return EXIT_FAILURE;

	// welcome user, give game instructions
	welcome();

	// display the first words a user should enter
	COUT << ENDL << "We recommend starting with one of the following words:" << ENDL;
	display_words(words, num_tries);

	// GAME LOOP:
	while (!end_game) {

		// get user input
		while(get_word(guessed_word, words)); // should run until it gets valid input

		// breaking or printing home screen
		if (guessed_word == "q") break;
		if (guessed_word == "h") {
			welcome();
			continue;
		}

		while(get_colors(guessed_word_colors)); // will run until valid user input

		// breaking if user requested to
		if (guessed_word_colors == "q") break;

		// breaking if they won
		if (guessed_word_colors == "ggggg") {
			COUT << ENDL << "Solved!" << ENDL << ENDL;
			break;
		}

		// increment num_tries -- indicates which try the user is on when they guess the next word
		num_tries++;
	
		// update letter_map accordingly
		err = update_letter_map(guessed_word, guessed_word_colors, letter_map);
		if (err) return EXIT_FAILURE;

		// search for words that work
		words = find_words(letter_map, words);

		// display the 10 highest ranked words
		end_game = display_words(words, num_tries);

		// if there are no possible words, they are out of guesses, or there is only one possible word, end the game
		if (end_game) {
			// if display_words returned a -1, it means there are no words to fit the criteria -- so the program
			// encountered an error somewhere or the word list is incomplete,
			if (end_game < 0) status = EXIT_FAILURE;
		}

	} 

	return status;
}
