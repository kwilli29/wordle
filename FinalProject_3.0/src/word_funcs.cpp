/******************************
 * Team: Beta Structures
 * Names: Danielle Croft, Hannah Long, Kate Mealey, Kelly Williams
 * Emails: dcroft@nd.edu, hlong3@nd.edu, kmealey2@nd.edu, kwilli29@nd.edu
 * File Name: word_funcs.cpp
 * Date Created: 04/14/2022
 * File Contents: This file contains the functions for a wordle solver
 *****************************/

#include "../include/word_funcs.h"



// swaps two values in a section
void swap(VECTOR<Word>& words, int i, int j) 
{
	Word temp = words[i];
	words[i] = words[j];
	words[j] = temp;
}



// function for quicksort
int partition(VECTOR<Word>& section, int lo, int hi, bool by_info)
{

	// decides to either sort by info_rank or common_rank
	if (by_info) {

		double pivot = section[hi].info_rank;

		int i = lo-1;

		for (int j=lo; j<hi; j++) {

			if (section[j].info_rank < pivot) {

				i++;

				swap(section, i, j);

			}

		}

		swap(section, i+1, hi);

		return i+1;

	}

	else {

		double pivot = section[hi].common_rank;

		int i = lo-1;

		for (int j=lo; j<hi; j++) {

			if (section[j].common_rank < pivot) {

				i++;

				swap(section, i, j);

			}

		}

		swap(section, i+1, hi);

		return i+1;

	}

}



// function for quicksort
void quicksort(VECTOR<Word>& tobeSorted, int lo, int hi, bool by_info)
{
	
	if (lo < hi) {

		int p = partition(tobeSorted, lo, hi, by_info);
		quicksort(tobeSorted, lo, p-1, by_info);
		quicksort(tobeSorted, p+1, hi, by_info);

	}

	return;

}



// reads in file and converts to Words
int read_file(VECTOR<Word>& the_words)
{
	// first read common words and create the unordered map
	IFSTREAM infile0;
	infile0.open("common-words.txt");

	// our file reader, iterator, and unordered map
	int iter = 0;
	STRING reader;
	UNOR_MAP< STRING, int > the_map;

	// while loop to read file
	while (infile0 >> reader) {
		
		// add to unordered map
		the_map.insert({reader, iter});

		// update iter
		iter++;

	}

	infile0.close();

	// declaring filestream
	IFSTREAM infile;
	infile.open("info-words.txt");

	// while loop to read file
	while (infile >> reader) {
		
		// create a wordle struct for the word
		// the map is used to find the commonality score of a word
		Word the_word(reader, the_map);

		// push back onto vector
		the_words.push_back(the_word);

	}

	infile.close();

	return 0;
}



// initializes the letter map
int init_letter_map(UNOR_MAP<char, VECTOR<Color> >& letter_map)
{

	int ascii_A = 97;
	int ascii_Z = 122;

	VECTOR<Color> pos_colors(5, NAN);

	// go through all of the lowercase letters
	for (int letter = ascii_A; letter <= ascii_Z; letter++) {

		letter_map.emplace((char)letter, pos_colors);

	}

	return 0;
}



// welcomes the user to our wordle solver
void welcome() {

	COUT 	<< "--------------------------------------------------------------------------------" << ENDL
			<< ENDL
			<< "                                   Welcome to                                   " << ENDL
			<< "                                  WORDLE SOLVER                                 " << ENDL
			<< ENDL
			<< "    Enter the word you put into Wordle, then its respective coloring result.    " << ENDL 
			<< "                                    a = gray                                    " << ENDL
			<< "                                   y = yellow                                   " << ENDL
			<< "                                   g = green                                    " << ENDL
			<< "For example, if the colors were gray, gray, green, yellow, green, enter 'aagyg'." << ENDL
			<< ENDL
			<< "              The algorithm will print the next best words to play.             " << ENDL
			<< "                    Enter h to print the welcome screen again.                  " << ENDL
			<< "                           Enter q at anytime to quit."                           << ENDL
			<< ENDL
			<< "--------------------------------------------------------------------------------" << ENDL
			<< ENDL;

	return;
}



// prompts user for word they have guessed and stores results in a string
int get_word(STRING &word, const VECTOR<Word> &words) {

	// prompt user
	COUT << ENDL << "Enter your guess:" << ENDL;

	// store response as string
	CIN >> word;

	// if the word was 'q', then they want to quit
	if ((word == "q") || (word == "h")) return 0;

	// check for validity:
	if (word.length() == 5) {

		for (size_t iter = 0; iter < words.size(); iter++) {
			if (words.at(iter).string.compare(word) == 0) return 0;
		}
	}

	CERR << "Error: Invalid word" << ENDL;

	return -1;
}



// prompts user for colors and saves their response as a string
int get_colors(STRING &colors) {

	// prompt user
	COUT << "Enter colors of letters:" << ENDL;

	// store response as string
	CIN >> colors;

	// if user entered "q", then they want to quit
	if (colors == "q") return 0;

	// check for validity:
	if (colors.length() != 5) {
		CERR << "Error: Must have one color for each letter in word" << ENDL;
		return -1;
	}

	// checks if user entered valid letters for colors
	for (size_t iter = 0; iter < colors.length(); iter++) {

		if (! ((colors.at(iter) == 'a') || (colors.at(iter) == 'g') || (colors.at(iter) == 'y'))) {

			CERR << "Error: Enter 'a' for gray, 'y' for yellow, or 'g' for green" << ENDL << ENDL;
			return -1;
		}
	}

	return 0;
}



// updates the letter map with the info from the user's guess
int update_letter_map(STRING word, STRING colors, UNOR_MAP<char, VECTOR<Color> > &letter_map) {

	// fixing word and colors to all be lowercase
	for (size_t i=0; i<word.length(); i++) {
		word[i] = (char)tolower(word[i]);
		colors[i] = (char)tolower(colors[i]);
	}
	
	VECTOR<size_t> gray_indices;
	VECTOR<char> g_y_letters;

	// iterate through letters and update letter_map at the letter at the place in word
	// to the color at the place in colors
	for (size_t iter = 0; iter < word.length(); iter++) {

		switch (colors.at(iter)) {

			case 'a' :
				letter_map[word.at(iter)].at(iter) = GRAY;  
				gray_indices.push_back(iter);
				break;

			case 'y' :
				letter_map[word.at(iter)].at(iter) = YELLOW;
				g_y_letters.push_back(word.at(iter));
				break;

			case 'g' :
				letter_map[word.at(iter)].at(iter) = GREEN;
				g_y_letters.push_back(word.at(iter));
				break;
		}
	}

	// if there are no yellow or green positions for the same letter that is gray
	// then we can safely remove it as a key from the map
	for (size_t i_gi = 0; i_gi < gray_indices.size(); i_gi++) {

		bool letter_full_gray = true;

		for (size_t i_gyl = 0; i_gyl < g_y_letters.size(); i_gyl++) {

			// if the letter is gray and yellow, then pass it
			if ( word[gray_indices[i_gi]] == g_y_letters[i_gyl] ) {

				letter_full_gray = false;
				break;

			}

		}

		// if letter_full_gray is still true, then we can remove from map
		if (letter_full_gray) {
			letter_map.erase( word[gray_indices[i_gi]] );
		}
	}

	return 0;
}



// finds the possible words that a user can put into wordle
VECTOR<Word> find_words(UNOR_MAP< char, VECTOR<Color> > letter_map, VECTOR<Word>& the_words)
{
	// initialize variables
	VECTOR<Word> new_words;
	bool valid_word;
	bool letter_found;
	UNOR_MAP< char, int > req_letters;

	// first, iterate through map to find the required letters
	for ( auto elem : letter_map ) {

		// loop through the current word's color vector
		for ( auto the_color : elem.second ) {

			// add to set
			if ((the_color == YELLOW) || (the_color == GREEN)) {

				// if the letter is not in the map yet
				if (req_letters.find(elem.first) == req_letters.end()) {
					req_letters.insert({elem.first, 1});
				} else {
					req_letters[elem.first]++;
				}

			}

		}

	}

	// iterate through the_words
	for ( unsigned int i=0; i<the_words.size(); i++ ) {

		// assume word is valid until proven otherwise
		valid_word = true;

		// first, iterate through the req_letters set and make sure it has all the needed letters
		if (!req_letters.empty()) {

			// iterating through the required letters
			for ( auto dummy : req_letters) {

				char curr_letter = dummy.first;

				// assume letter is not there
				letter_found = false;

				// iterating through the letters in the string to see if that letter is there
				for ( auto word_sec : the_words[i].string ) {

					// if letter found, then set to true
					if ( word_sec == curr_letter ) {
						letter_found = true;
						break;
					}

				}

				// if letter_found is still false, then this word is not valid.
				// break and continue
				if (letter_found == false) {
					valid_word = false;
					break;
				}

				// if there is multiple of that letter, than we need to make sure this word has the right amount
				if (dummy.second > 1) {
					
					int num_letters = 0;

					// iterate through the word to find number of times that letter appears
					for (unsigned int k=0; k<the_words[i].string.size(); k++) {
						if (the_words[i].string[k] == dummy.first) num_letters++;
					}

					// if letter does not appear enough, then the word is not valid
					if (num_letters < dummy.second) {
						valid_word = false;
						break;
					}

				}

				// now, we need to make sure that if this req_letter is green, that it's in the right position
				// iterate through the letter_map to find if there is a green somewhere
				for (unsigned int j=0; j<letter_map[curr_letter].size(); j++) {
					
					// if the color is green, then make sure that letter is at that position in the word
					if (letter_map[curr_letter].at(j) == GREEN) {
						
						// test the word to see if it has that green letter at the correct spot
						if (the_words[i].string.at(j) != curr_letter) {
							valid_word = false;
							break;
						}

					}

				}

				// breaks here if a test was not passed
				if (valid_word == false) break;
	
			}

		} 

		// if word is still false, then continue on to analyze next word
		if (valid_word == false) continue;

		// Now, we need to test the position of each letter in the word
		// iterate through the word's letters
		for (unsigned int j=0; j<the_words[i].string.length(); j++) {

			char curr_letter = the_words[i].string[j];

			// first make sure the letter is in the map
			if ( letter_map.find(curr_letter) == letter_map.end() ) {

				// if we are here, then the letter is not in the map
				// word is not valid anymore; set to false and break
				valid_word = false;
				break;

			}

			// now, test against the letter_map
			// if gray or yellow IN THE SAME POSITION, then set to false and break
			if ((letter_map[curr_letter].at(j) == YELLOW) || (letter_map[curr_letter].at(j) == GRAY)) {
				valid_word = false;
				break;
			}

		}

		// if word is still true, then push it onto new_words
		if (valid_word) new_words.push_back( the_words[i] ); 

	}

	// return the words
	return new_words;
}



// displays the word to the user in a ranked score
int display_words(VECTOR<Word>& the_words, int num_tries)
{

	COUT << ENDL;

	// if there are no possible words
	if (the_words.size() == 0) {
		COUT << "No possible words." << ENDL << ENDL;
		return 1;
	}

	// sorting the words depending if on by info or by commonality
	if (num_tries > 2) {

		// quicksort by commonality
		quicksort(the_words, 0, (int)the_words.size()-1, false);

		// displaying the words
		for (unsigned int i=1; i<=the_words.size(); i++) {

			COUT << i << ": " << the_words[i-1].string << ENDL;

			// only want to display first 10 words, so break here
			if (i == 10) break;

		}

	} else {

		// quicksort by info
		quicksort(the_words, 0, (int)the_words.size()-1, true);

		// displaying the words
		for (unsigned int i=1; i<=the_words.size(); i++) {

			COUT << i << ": " << the_words[the_words.size()-i].string << ENDL;

			// only want to display first 10 words, so break here
			if (i == 10) break;

		}


	}

	return 0;
}
