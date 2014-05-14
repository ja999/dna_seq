#include "population.h"

Population::Population(WordsGraph *graph) {
	for (int i=0; i<size; i++) {
		Specimen spec(graph);
		objects.push_back(spec);
	}
}

void Population::tpx(Specimen first, Specimen second) {
	int random1 = rand() % first.specimen_indexes.size(),
	random2 = rand() % first.specimen_indexes.size(),
	random3 = rand() % first.specimen_indexes.size();

	vector<int> childIndexes1, childIndexes2;
	vector<int> crossoverPionts;
	crossoverPionts.push_back(0);
	crossoverPionts.push_back(random1);
	crossoverPionts.push_back(random2);
	crossoverPionts.push_back(random3);
	crossoverPionts.push_back(first.specimen_indexes.size());
	sort(crossoverPionts.begin(), crossoverPionts.end());

	for (int i=0; i<crossoverPionts.size()-1; i++) {
		for (int j=crossoverPionts[i]; j<crossoverPionts[i+1]; j++) {
			if (i % 2) {
				childIndexes1.push_back(first.specimen_indexes[j]);
				childIndexes2.push_back(second.specimen_indexes[j]);
			} else {
				childIndexes1.push_back(second.specimen_indexes[j]);
				childIndexes2.push_back(first.specimen_indexes[j]);
			}
		}
	}

	Specimen child1(first.graph, childIndexes1);
	Specimen child2(first.graph, childIndexes2);

	objects.push_back(child1);
	objects.push_back(child2);

	//child1.print();
	//child2.print();
}

void Population::sortPopulation() {
	sort(objects.begin(), objects.end(), Specimen::compare);
}

void Population::scxCrossover() {
	vector<Specimen> offsprings(size/4, objects[0]);
	for (int i=0; i<size/4; i++) {
		Specimen a = objects[i];
		Specimen b = objects[rand() % size];
		Specimen c = a.scx(b);
		offsprings.at(i) = c;
	}
	objects.insert(objects.end(),offsprings.begin(),offsprings.end());

	for (int i=0; i<size/4; i++) {
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

void Population::tpxCrossover() {
	for (int i=0; i<size/2; i++) {
		int random = rand() % size;
		int random2 = rand() % size;
		Specimen a = objects[random];
		while (random == random2)
			random2 = rand() % size;
		Specimen b = objects[random2];
		tpx(a, b);
	}
}

void Population::mutate() {
	for (int i = 0; i<size; i++)
		if (rand() % 100 < 30) {
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

void Population::merge(Population second) {
	objects.insert(objects.end(),second.objects.begin(),second.objects.end());
	size +=second.size;
}

void Population::evolve() {
	sortPopulation();
	//cout<<"scx"<<endl;
	scxCrossover();
	//cout<<"tpx"<<endl;
	tpxCrossover();
	mutate();
	getNextGeneration();
}
