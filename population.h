#ifndef POPULATION_H
#define POPULATION_H

#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include "specimen.h"

using namespace std;

class Population {
	public:
		vector<Specimen> objects;
		Population(WordsGraph *graph);
		void merge(Population second);
		void tpx(Specimen first, Specimen second);
		void evolve();
		void getNextGeneration();
		void sortPopulation();
		void scxCrossover();
		void tpxCrossover();
		void mutate();
		int size = 1200;
};

#endif
