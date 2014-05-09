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

int main(int argc, char* argv[]) {
  srand(unsigned(time(0)));
	vector<Population*> populations;
	int popSize = 10;
	vector<Word> words;
	getData(words);
	WordsGraph *graph = new WordsGraph(words);
	/*
	Population initial_pop(graph);
	for (int i=0; i<50; i++) {
		initial_pop.evolve();
		initial_pop.objects.front().printStats();
	}*/
	for (int i=0; i<popSize; i++) {
		//Population pop(graph);
		populations.push_back(new Population(graph, atoi(argv[1])));
	}
	while(populations.size() > 0) {
		for (int i=0; i<10; i++) {
			cout<<populations.size()<<endl;
			for (Population* pop : populations) {
				pop->evolve();
				pop->objects.front().printStats();
			}
			// for (Specimen spec : initial_pop.objects) {
			// 	spec.printStats();
			// }
		}
		for (Population* pop : populations) 
			pop->objects.front().printStats();
		for (int i=0; i<populations.size()/2; i++) {
			populations.at(i)->merge(*(populations.at(i+1)));
			populations.erase(populations.begin()+i+1);
		}
	}
	return 0;
}
