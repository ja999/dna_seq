#ifndef POPULATION_H
#define POPULATION_H

#include <algorithm>
#include <vector>
#include <string>
#include "specimen.h"

using namespace std;

class Population {
	public:
		Population(WordsGraph *newGraph);
    vector<Specimen> objects;
    void evolve();
    void getNextGeneration();
		int size = 100;
};

#endif
