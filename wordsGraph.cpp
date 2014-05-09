#include "wordsGraph.h"

WordsGraph::WordsGraph(vector<Word> words, int n) : n(n) {
	this->words = words;
	matrix = new int* [words.size()];
	for (int i=0; i<words.size(); i++) {
		matrix[i] = new int [words.size()];
		vector<int> patternHash = words.at(i).getPatternHash();
		for (int j=0; j<words.size(); j++) {
			if (i == j)
				matrix[i][j] = -1;
			else
				matrix[i][j] = words.at(j).overlap(patternHash);
		}
	}
}

WordsGraph::~WordsGraph() {
	for (int i=0; i<words.size(); i++)
		delete [] matrix[i];
	delete [] matrix;
}

Word WordsGraph::getWord(int i) {
	return words.at(i);
}

int WordsGraph::getN() {
	return n;
}

int WordsGraph::getSize() {
	return words.size();
}

void WordsGraph::print() {
	for (Word word : words)
		cout<<"\t"<<word.getText();
	cout<<endl;
	for (int i=0; i<words.size(); i++) {
		cout<<words.at(i).getText();
		for (int j=0; j<words.size(); j++)
			cout<<"\t"<<getOverlap(i,j);
		cout<<endl;
	}
}

int WordsGraph::getOverlap(int first, int second) {
	return matrix[first][second];
}
