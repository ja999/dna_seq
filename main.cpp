#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "population.h"
#include "specimen.h"
#include "debug.h"
#include "word.h"

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
	vector<Word> words;
	getData(words);
	WordsGraph graph(words);
	return 0;
}
