#ifndef WORDLE_WORD_H
#define WORDLE_WORD_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <fstream>
#include <queue>

#define STRING std::string
#define VECTOR std::vector
#define UNOR_MAP std::unordered_map
#define SET std::set
#define COUT std::cout
#define CIN std::cin
#define ENDL std::endl
#define IFSTREAM std::ifstream
#define OFSTREAM std::ofstream
#define QUEUE std::queue

struct wordle_word {

	public:

		// the members of the word
		STRING word;
		double score;
		bool valid;
		UNOR_MAP< char, SET<int> > indices;

		// Default Constructor
		wordle_word(): word(), score(), valid(), indices() {}

		// Overloaded Constructor	
		wordle_word(STRING the_word) : word(the_word) {
			
			valid = true;

			// filling the unordered map
			fill_map(indices, the_word);

			// finding the words score
			score = find_score(indices);

		}


	private:

		// fills an unordered_map< char, set<int> >
		void fill_map(UNOR_MAP< char, SET<int> >& the_map, const STRING the_word) {

			for (int i=0; i<5; i++) {

				// if not in map, add it to map and start the set
				if (the_map.find(the_word[i]) == the_map.end()) {
					SET<int> the_set;
					the_set.insert(i);
					the_map.insert({the_word[i], the_set});

				// if already in map, add index to the set
				} else {
					the_map[the_word[i]].insert(i);
				}
			}

		}

		// finds the score of a word
		double find_score(const UNOR_MAP<char, SET<int> > the_map) {

			double the_score = 0;

			for (auto x : the_map) {
			
				switch(tolower(x.first)) {

					case 'a':
						the_score += 9.24;
						break;

					case 'b':
						the_score += 2.51;
						break;

					case 'c':
						the_score += 3.12;
						break;

					case 'd':
						the_score += 3.78;
						break;

					case 'e':
						the_score += 10.28;
						break;

					case 'f':
						the_score += 1.72;
						break;

					case 'g':
						the_score += 2.53;
						break;

					case 'h':
						the_score += 2.71;
						break;

					case 'i':
						the_score += 5.8;
						break;

					case 'j':
						the_score += 0.45;
						break;

					case 'k':
						the_score += 2.31;
						break;

					case 'l':
						the_score += 5.2;
						break;

					case 'm':
						the_score += 3.05;
						break;

					case 'n':
						the_score += 4.55;
						break;

					case 'o':
						the_score += 6.84;
						break;

					case 'p':
						the_score += 3.11;
						break;

					case 'q':
						the_score += 0.17;
						break;

					case 'r':
						the_score += 6.42;
						break;

					case 's':
						the_score += 10.27;
						break;

					case 't':
						the_score += 5.09;
						break;

					case 'u':
						the_score += 3.87;
						break;

					case 'v':
						the_score += 1.07;
						break;

					case 'w':
						the_score += 1.6;
						break;

					case 'x':
						the_score += 0.44;
						break;

					case 'y':
						the_score += 3.2;
						break;

					case 'z':
						the_score += 0.67;

				}

			}

			return the_score;

		}

};

#endif
