#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <string>
#include "specimen.h"

using namespace std;

class Population {
	public:
		vector<Specimen> objects;
		Population(WordsGraph *graph);
		int size = 100;
};

#endif
