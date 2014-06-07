#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "population.h"
#include "specimen.h"
#include "debug.h"
#include "word.h"
#include "wordsGraph.h"
#include "parameters.h"

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
	if (argc < 2) {
		cout<<"I need N... as argument."<<endl;
		return 0;
	}
  srand(unsigned(time(0)));
	vector<Population*> populations;
	vector<Word> words;
	getData(words);
	WordsGraph *graph = new WordsGraph(words, atoi(argv[1]));
	cout<<graph->getN()<<endl;

	cout<<"TEST"<<endl;
	for (int i=0; i<POPULATION_COUNT; i++) {
		populations.push_back(new Population(graph));
	}
	cout<<"TEST"<<endl;

	while (populations.size() > 0) {
		for (int i=0; i<GENERATION_COUNT; i++) {
			cout<<populations.size()<<endl;

			#pragma omp parallel for
			for (int i=0; i<populations.size(); i++) {
				populations[i]->evolve();
				//populations[i]->objects.front().printStats();
			}
		}

		for (Population* pop : populations)
			pop->objects.front().printStats();
		if (populations.size() == 1)
			return 0;

		for (int i=0; i<populations.size()/2; i++) {
			populations.at(2*i)->merge(*(populations.at(2*i+1)));
		}
		for (int i=1; i<populations.size(); i++) {
			populations.erase(populations.begin()+i);
		}
	}
	return 0;
}
