#ifndef SPECIMEN_H
#define SPECIMEN_H

#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include "wordsGraph.h"

using namespace std;

class Specimen {
	private:
		int* nextIndexes;
		int getNextIndex(int index);
		void fix(vector<bool>& visited, queue<int>& toFix);
	public:
		WordsGraph *graph;
		Specimen(WordsGraph *graph);
		Specimen(WordsGraph *graph, vector<int> specimen_indexes);
		static Specimen random(WordsGraph *graph);
		Specimen scx(Specimen second);
		vector<int> specimen_indexes;
		string specimen_aligned = "";
		int alignment_length = -1;
		static bool compare(Specimen a, Specimen b);
		int calculateFitness();
		bool validate();
		void print();
		void printStats();
};

#endif
