#include "population.h"

Population::Population(WordsGraph *graph) {
	for (int i=0; i<size; i++) {
		objects.push_back(Specimen::random(graph));
	}
}
