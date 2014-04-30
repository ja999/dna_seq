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
	for (int i=0; i<size/4; i++) {
		Specimen a = objects[i];
		Specimen b = objects[rand() % size];
		Specimen c = a.ppx(b);
		objects.push_back(c);
	}

	for (int i=0; i<size/4; i++) {
		int random = rand() % size;
		int random2 = rand() % size;
		Specimen a = objects[random];
		while (random == random2)
			random2 = rand() % size;
		Specimen b = objects[random2];
		Specimen c = a.ppx(b);
		objects.push_back(c);
	}
}

void Population::mutate() {
	for (int i = 0; i<size; i++)
		if (rand() % 100 < 10) {
			int randomSpecimen = rand() % size;
			int randomWord1 = rand() % objects[randomSpecimen].specimen_indexes.size();
			int randomWord2 = rand() % objects[randomSpecimen].specimen_indexes.size();
			Specimen a = objects[randomSpecimen];
			swap(a.specimen_indexes[randomWord1], a.specimen_indexes[randomWord2]);
		}
}

void Population::getNextGeneration() {
	if (objects.size() > size) {
		vector<Specimen> newObjects;
		for (int i=0; i<size; i++) {
			newObjects.push_back(objects[i]);
		}
	}
}

void Population::evolve() {
	sortPopulation();
	crossover();
	mutate();
	getNextGeneration();
}
