#include "specimen.h"

Specimen::Specimen(WordsGraph *newGraph) {
  this->graph = newGraph;
  for (int i=0; i<graph->getSize(); i++) {
    specimen_indexes.push_back(i);
  }
  random_shuffle(specimen_indexes.begin(), specimen_indexes.end());
  calculateFitness();
}

int Specimen::calculateFitness() {
	int result = 0;
	for (int i=1; i<specimen_indexes.size(); i++) {
		result += graph->getOverlap(specimen_indexes.at(i-1),specimen_indexes.at(i));
	}
	alignment_length = result;
	return result;
}

void Specimen::print() {
  for (int i=0; i<specimen_indexes.size(); i++) {
    cout<<specimen_indexes[i]<<' ';
  }
  cout<<endl;
  cout<<"Specimen size: "<<specimen_indexes.size()<<endl;
  cout<<"Specimen alignment_length: "<<alignment_length<<endl;
}

bool Specimen::compare(Specimen a, Specimen b) {
  if (a.alignment_length < b.alignment_length)
    return true;
  else
    return false;
}
