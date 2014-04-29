#include "specimen.h"

int Specimen::calculateFitness() {
	int result = 0;
	for (int i=1;i<specimen_indexes.size();i++) {
			result += graph->getOverlap(i-1,i);
	}
  alignment_length = result;
	return result;
}

