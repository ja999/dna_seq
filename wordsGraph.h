#ifndef WORDSGRAPH_H
#define WORDSGRAPH_H
#include "word.h"
using namespace std;
class WordsGraph {
	private:
		vector<Word> words;
		int pattern;
		vector<int> patternHash;
		int overlap(int pattern, int second);
	public:
		~WordsGraph();
		WordsGraph (vector<Word> words);
		int ** matrix;
		int getOverlap(int first, int second);
		int getSize();
		void print();
};

#endif /* WORDSGRAPH_H */
