#ifndef SPECIMEN_H
#define SPECIMEN_H

#include <vector>
#include <string>
#include "wordsGraph.h"
using namespace std;

class Specimen {
	private:
		WordsGraph *graph;
	public:
		vector<int> specimen_indexes;
		string specimen_aligned;
		int alignment_length = -1;
		int calculateFitness();
};

#endif
