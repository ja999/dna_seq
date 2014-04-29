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
		Specimen(WordsGraph *graph);
		static Specimen random(WordsGraph *graph);
		Specimen scx(Specimen second);
		vector<int> specimen_indexes;
		string specimen_aligned = "";
		int alignment_length = -1;
		int calculateFitness();
		void print();
};

#endif
