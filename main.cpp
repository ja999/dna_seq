#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "population.h"
#include "specimen.h"
#include "debug.h"
#include "word.h"
#include "wordsGraph.h"

using namespace std;

int getData(vector<Word> &words) {
	while (cin) {
		string word;
		cin>>word;
		if (!word.empty())
			words.push_back(Word(word));
	}
	return 0;
}

int main() {
  srand(unsigned(time(0)));

	vector<Word> words;
	getData(words);
	WordsGraph *graph = new WordsGraph(words);
	Population initial_pop(graph);
	initial_pop.getNextGeneration();
	for (Specimen spec : initial_pop.objects) {
		spec.print();
	}
	return 0;
}
