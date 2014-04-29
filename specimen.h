#ifndef SPECIMEN_H
#define SPECIMEN_H

#include <vector>
#include <algorithm>
#include <string>
#include "wordsGraph.h"

using namespace std;

class Specimen {
	private:
		WordsGraph *graph;
	public:
		Specimen(WordsGraph *newGraph);
		vector<int> specimen_indexes;
		string specimen_aligned = "";
		int alignment_length = -1;
    static bool compare(Specimen a, Specimen b);
		int calculateFitness();
		void print();
};

#endif
