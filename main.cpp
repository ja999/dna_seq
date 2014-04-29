#include <iostream>
#include <string>
#include <cmath>

#include "population.h"
#include "specimen.h"

using namespace std;

int main() {
	vector<Word> words;
	while(cin) {
		string word;
		cin>>word;
		words.push_back(Word(word));
	}
	WordsGraph graph(words);
	graph.print();
	return 0;
}
