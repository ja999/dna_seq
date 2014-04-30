#ifndef POPULATION_H
#define POPULATION_H

#include <algorithm>
#include <vector>
#include <string>
#include "specimen.h"

using namespace std;

class Population {
	public:
		vector<Specimen> objects;
		Population(WordsGraph *graph);
		void evolve();
		void getNextGeneration();
    void sortPopulation();
    void crossover();
    void mutate();
		int size = 600;
};

#endif
