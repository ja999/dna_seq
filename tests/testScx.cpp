#include<iostream>
#include "../word.h"
#include "../wordsGraph.h"
#include "../debug.h"
#include "../specimen.h"
#include<vector>
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

int main () {
#ifdef DEBUG
	cout<<"DEBUG ON"<<endl;
#endif
	srand(time(0));
	vector<Word> words;
	getData(words);
	WordsGraph *graph = new WordsGraph(words);
	cout<<"debug"<<endl;
	Specimen first(graph);
	cout<<"debug"<<endl;
	Specimen second(graph);
	cout<<"debug"<<endl;
	Specimen child = first.scx(second);
	first.print();
	second.print();
	child.print();
	return 0;
}
