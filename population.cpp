#include "population.h"

Population::Population(WordsGraph *newGraph) {
  for (int i=0; i<size; i++) {
    Specimen spec(newGraph);
    objects.push_back(spec);
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
