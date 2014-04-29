#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <string>
#include "specimen.h"

using namespace std;

class Population {
	private:
		vector<Specimen> objects;
	public:
		Population();
		int size = 100;
		int randomize();
};

#endif
