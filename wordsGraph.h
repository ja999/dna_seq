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
		int n;
	public:
		~WordsGraph();
		WordsGraph (vector<Word> words, int n);
		int ** matrix;
		int getOverlap(int first, int second);
		int getSize();
		int getN();
		Word getWord(int i);
		void print();
};

#endif /* WORDSGRAPH_H */
