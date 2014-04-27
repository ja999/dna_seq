#include<iostream>
#include "../word.h"
#include "../wordsGraph.h"
#include "../debug.h"
#include<vector>
using namespace std;
int main () {
#ifdef DEBUG
	cout<<"DEBUG ON"<<endl;
#endif
	vector<Word> words;
	while(1) {
		string word;
		cin>>word;
		if(word!="do") {
			words.push_back(Word(word));
		}
		else
			break;
	}
	WordsGraph graph(words);
	graph.print();
	return 0;
}
