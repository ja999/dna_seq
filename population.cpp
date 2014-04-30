#include "population.h"

Population::Population(WordsGraph *graph) {
	for (int i=0; i<size; i++) {
		Specimen spec(graph);
		objects.push_back(spec);
	}
}

void Population::sortPopulation() {
	sort(objects.begin(), objects.end(), Specimen::compare);
}

void Population::crossover() {
	vector<Specimen> offsprings(size/2, objects[0]);
#pragma omp parallel for
	for (int i=0; i<size/2; i++) {
		Specimen a = objects[i];
		Specimen b = objects[rand() % size];
		Specimen c = a.scx(b);
		offsprings.at(i) = c;
	}
	objects.insert(objects.end(),offsprings.begin(),offsprings.end());

#pragma omp parallel for
	for (int i=0; i<size/2; i++) {
		int random = rand() % size;
		int random2 = rand() % size;
		Specimen a = objects[random];
		while (random == random2)
			random2 = rand() % size;
		Specimen b = objects[random2];
		Specimen c = a.scx(b);
		offsprings.at(i) = c;
	}
	objects.insert(objects.end(),offsprings.begin(),offsprings.end());

}

void Population::mutate() {
	for (int i = 0; i<size; i++)
		if (rand() % 100 < 50) {
			int randomSpecimen = rand() % size;
			int randomWord1 = rand() % objects[randomSpecimen].specimen_indexes.size();
			int randomWord2 = rand() % objects[randomSpecimen].specimen_indexes.size();
			Specimen a = objects[randomSpecimen];
			swap(a.specimen_indexes[randomWord1], a.specimen_indexes[randomWord2]);
			objects.push_back(a);
		}
}

void Population::getNextGeneration() {
	vector<Specimen> newObjects;
	sortPopulation();
	if (objects.size() > size) {
		for (int i=0; i<size; i++) {
			newObjects.push_back(objects[i]);
		}
		objects = newObjects;
	}
}

void Population::evolve() {
	sortPopulation();
	crossover();
	mutate();
	getNextGeneration();
}
