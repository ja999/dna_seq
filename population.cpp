#include "population.h"

Population::Population(WordsGraph *graph) {
	for (int i=0; i<size; i++) {
		objects.push_back(Specimen::random(graph));
	}
}

void Population::evolve() {

}

void Population::getNextGeneration() {
  sort(objects.begin(), objects.end(), Specimen::compare);
  if (objects.size() > size) {
    vector<Specimen> newObjects;
    for (int i=0; i<size; i++) {
      newObjects.push_back(objects[i]);
    }
  }
}
