#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <set>
#include <fstream>
#include <queue>
#include <climits>
#include <limits>
#include <cstdlib>

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
#define CERR std::cerr

typedef struct Word {

	public:

		// the members of the word
		STRING string;
		double info_rank;
		double common_rank;

		// Default Constructor
		Word() : string(), info_rank(), common_rank() {}

		// Overloaded Constructor	
		Word(STRING string_in, UNOR_MAP< STRING, int > the_map) : string(string_in) {

			// finding the info rank of a word
			double the_score = 0;

			// vector to keep track of what words we have encountered
			SET<char> the_letters;

			for (auto x : this->string) {

				// make sure x is NOT in set, then add to score
				if ( the_letters.find(x) == the_letters.end() ) {

					the_letters.insert(x);
			
					switch(tolower(x)) {

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
							break;

					}

				}

			}

			info_rank = the_score;

			// finding the commonality of a word, using a map that references the common-words file
			if (the_map.find(string_in) == the_map.end()) {
				common_rank = (double)the_map.size();
			} else {
				common_rank = (double)the_map[string_in];
			}

		}

} Word;

#endif
