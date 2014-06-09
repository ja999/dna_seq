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

int getData(ifstream& input, vector<Word> &words) {
	while (input.good()) {
		string word;
		input>>word;
		if (!word.empty())
			words.push_back(Word(word));
	}
	input.close();
	return 0;
}

int main(int argc, char* argv[]) {
	bool files = false;
	if (argc < 2) {
		cout<<"I need N... as argument."<<endl;
		return 0;
	}
	else if (argc > 3) {
		files = true;
	}
	srand(unsigned(time(0)));
	vector<Population> populations;
	vector<Word> words;
	ofstream output;
	if(files) {
		ifstream input(argv[2]);
		output.open(argv[3]);
		if (!input.is_open()) {
			cout<<"input file error";
			return 0;
		}
		else if (!output.is_open()) {
			cout<<"output file error";
			input.close();
			return 0;
		}
		getData(input,words);
	}
	else {
		getData(words);
	}
	WordsGraph *graph = new WordsGraph(words, atoi(argv[1]));
	cout<<graph->getN()<<endl;

	for (int i=0; i<POPULATION_COUNT; i++) {
		populations.emplace_back(graph);
	}

	while (populations.size() > 0) {
		for (int i=0; i<GENERATION_COUNT; i++) {
			cout<<populations.size()<<endl;

			#pragma omp parallel for
			for (int i=0; i<populations.size(); i++) {
				populations[i].evolve();
				//populations[i]->objects.front().printStats();
			}
		}

		//cout<<"after evolve"<<endl;
		for (Population pop : populations)
			(*pop.specimenSet->begin()).printStats(output);
		//cout<<"pop"<<endl;
		if (populations.size() == 1) {
			(*populations.front().specimenSet->begin()).print(output);
			output.close();
			return 0;
		}

		//cout<<"before merge"<<endl;
		for (int i=0; i<populations.size()/2; i++) {
			populations.at(2*i).merge(populations.at(2*i+1));
		}
		//cout<<"before erase"<<endl;
		for (int i=1; i<populations.size(); i++) {
			populations.erase(populations.begin()+i);
		}
	}
	return 0;
}
