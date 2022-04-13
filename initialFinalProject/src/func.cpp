#include "../include/wordle_word.h"

// algorithm to partition for quicksort
int partition(VECTOR<double>& section, int lo, int hi)
{

	double pivot = section[hi];
	int i = lo-1;

	for (int j=lo; j<hi; j++) {

		if (section[j] < pivot) {

			i++;
			// swap here
			double temp = section[j];
			section[j] = section[i];
			section[i] = temp;
	
		}

	}

	double temp2 = section[i+1];
	section[i+1] = section[hi];
	section[hi] = temp2;

	return i+1;

}



// performs quicksort
void quicksort(VECTOR<double>& tobeSorted, int lo, int hi)
{

	if (lo < hi) {

		int p = partition(tobeSorted, lo, hi);
		quicksort(tobeSorted, lo, p-1);
		quicksort(tobeSorted, p+1, hi);

	}

}



// reads in file and converts to wordle words
int read_file(const STRING filename, VECTOR<wordle_word>& the_words)
{
	// declaring filestream
	IFSTREAM infile;
	infile.open(filename);

	// if file does not exist
	if (infile == NULL) {
		COUT << "File does not exist" << ENDL;
		return -1;
	}

	// our file reader
	STRING reader;

	// while loop to read file
	while (infile >> reader) {
		
		// create a wordle struct for the word
		wordle_word the_word(reader);

		// push back onto vector
		the_words.push_back(the_word);

	}

	infile.close();

	return 0;

}



// intializes the positions vector
void init_pos(VECTOR< SET<char> >& positions) 
{

	// initializing the set
	SET<char> the_set = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
						 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
						 'y', 'z'};

	// go through vector
	for (int i=0; i<5; i++) {
		
		// pushing onto vector
		positions.push_back(the_set);

	}

	return;
}



// finds the next words that could be entered by the user
VECTOR<wordle_word> find_words(const VECTOR<wordle_word> possible_words, const VECTOR< SET<char> > positions, const UNOR_MAP< char, unsigned int > req_letters)
{

	// the recommended words we will return
	VECTOR<wordle_word> rec_words;

	// iterating through the possible_words vector
	for (auto the_word : possible_words) {

		// if the word isn't valid, then continue
		if (the_word.valid == false) continue;

		// first iterate through req_letters to see if the word contains all the needed
		// letters
		for (auto needed_letter : req_letters) {

			// if word is not valid
			if (the_word.valid == false) break;
			
			// if letter not in wordle_word map
			if (the_word.indices.find(needed_letter.first) == the_word.indices.end()) {
				
				the_word.valid = false;

			// the letter IS in the wordle_word map, we need to check if there is the right amount of that letter
			} else {

				// not enough of that letter is present
				if (the_word.indices[needed_letter.first].size() < needed_letter.second) {

					the_word.valid = false;

				}

			}

		}

		// if the word is still valid, then we need to test it against the positions vector
		if (the_word.valid) {

			// iterate through the_word unordered map
			for (auto elem : the_word.indices) {

				// if the word is invalid, then break
				if (the_word.valid == false) break;

				// go through the values in the set in relation to positions
				for (auto curr_index : elem.second) {

					// if the positions vector at that index does not contain the letter
					if (positions[curr_index].find(elem.first) == positions[curr_index].						  end()) {
				
						the_word.valid = false;

						break;

					}

				}

			}

		}

		// if word is still valid, then add it to rec_words
		if (the_word.valid) {
		
			rec_words.push_back(the_word);

		}

	}

	return rec_words;

}



// prints the five best words that a user should choose
void best_words(VECTOR<wordle_word> rec_words)
{

	// printing amount of possible words
	COUT << rec_words.size() << " possible words" << ENDL << ENDL;

	// create vector of doubles to hold the score
	VECTOR<double> the_scores;
	for (auto elem : rec_words) {
		the_scores.push_back(elem.score);
	}

	// sort the scores
	quicksort(the_scores, 0, (int)the_scores.size()-1);

	// iterating through rec_words to print the rankings
	for (unsigned int rank_count=1; rank_count<=10; rank_count++)

		for (unsigned int i=0; i<rec_words.size(); i++) {

			if (rec_words[i].valid == false) continue;

			// print the word with the top score
			if (rec_words[i].score == the_scores[the_scores.size()-rank_count]) {
				COUT << rank_count << ": " << rec_words[i].word << ENDL;
				rec_words[i].valid = false;
				break;
			}

	}

	return;
}



// if a letter returned gray
void gray_letter(const char letter, const unsigned int index, VECTOR< SET<char> >& positions, UNOR_MAP< char, unsigned int >& req_letters)
{

	// if the current letter is in req letters, than we ONLY delete from current position
	if (req_letters.find(letter) != req_letters.end()) {
		
		positions[index].erase(letter);
		return;

	}

	// iterating through positions
	for (int iter=0; iter<5; iter++) {

		positions[iter].erase(letter);

	}

}



// if a letter returned yellow
void yellow_letter(const char letter, const unsigned int index, VECTOR< SET<char> >& positions, UNOR_MAP< char, unsigned int >& req_letters)
{
	// delete the letter from the index where it was yellow
	positions[index].erase(letter);

	// add this letter to unordered map
	if (req_letters.find(letter) == req_letters.end()) {

		// add to unordered map
		req_letters.insert({letter, 1});

	}

	return;
}



// if a letter returned green
void green_letter(const char letter, const unsigned int index, VECTOR< SET<char> >& positions, UNOR_MAP< char, unsigned int >& req_letters)
{
	// erase everything in the positions vector at that index EXCEPT for the letter
	positions[index].clear();
	positions[index].insert(letter);


	// add this letter to unordered map, or increment it
	if (req_letters.find(letter) == req_letters.end()) {

		// add to unordered map
		req_letters.insert({letter, 1});

	}

	return;
}



// prunes our structures based on result from wordle
void prune_structures(const STRING result, const wordle_word user_word, VECTOR< SET<char> >& positions, UNOR_MAP< char, unsigned int >& req_letters)
{

	// updating req_letters
	for (int j=0; j<5; j++) {

		if ((result[j] == 'g') || (result[j] == 'y')) {
			
			// add to map if not in it
			if (req_letters.find(result[j]) == req_letters.end()) {

				req_letters.insert({user_word.word[j], 1});

			}

		}

	}

	// managing special case where a word has multiple letters
	for (auto key : user_word.indices) {

		// if the set is longer than 1
		if (key.second.size() > 1) {

			unsigned int num_duplicates = 0;

			// test the results; see if the answer has multiple of that letter too
			for (auto set_elem : key.second) {

				if (result[set_elem] == 'g') num_duplicates++;
				else if (result[set_elem] == 'y') num_duplicates++;

			}

			// update the map of req letters to represent these duplicates
			req_letters[key.first] = num_duplicates;

		}

	}

	// iterate through result
	for (unsigned int iter=0; iter<5; iter++) {

		char color = result[iter];

		// depending on what color, perform different actions
		switch (color) {

			case 'a':
				gray_letter(user_word.word[iter], iter, positions, req_letters);
				break;

			case 'y':
				yellow_letter(user_word.word[iter], iter, positions, req_letters);
				break;

			case 'g':
				green_letter(user_word.word[iter], iter, positions, req_letters);
				break;

		}

	}

	return;
}
