#include "../include/func.h"

int main()
{
	// initialize structures
	VECTOR<wordle_word> possible_words;
	VECTOR< SET<char> > positions;
	UNOR_MAP< char, unsigned int > req_letters;

	// read in text file
	read_file("words.txt", possible_words);

	// initialize positions vector
	init_pos(positions);

	// tell user to start with the best words
	VECTOR<wordle_word> rec_words = find_words(possible_words, positions, req_letters);
	best_words(rec_words);

	// intializing user input
	STRING user_word;
	COUT << ENDL << "Enter the word you put into wordle (or q to quit): ";
	CIN >> user_word;

	// stores the result of the colors
	STRING result;

	// while loop to keep algorithm running
	while (user_word != "q") {

		COUT << "Enter the color results of that word: ";
		CIN >> result;
		COUT << ENDL;

		// creating temp wordle struct for the user_word
		wordle_word temp_wordle_word(user_word);

		// pruning the structures based on the result
		prune_structures(result, temp_wordle_word, positions, req_letters);

		// finding the potential words
		rec_words = find_words(possible_words, positions, req_letters);

		// finding the highest scoring words
		best_words(rec_words);

		COUT << ENDL << "Enter the word you put into wordle (or q to quit): ";
		CIN >> user_word;

	}

	return 0;
}
