#include "population.h"

Population::Population(WordsGraph *newGraph) {
  for (int i=0; i<size; i++) {
    Specimen spec(newGraph);
    objects.push_back(spec);
  }
}
