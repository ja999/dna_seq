#include "population.h"

Population::Population(WordsGraph *graph) {

  	bool(*fn_pt)(Specimen,Specimen) = Specimen::compare;
	specimenSet = new set<Specimen,bool(*)(Specimen,Specimen)>(fn_pt);
	while (specimenSet->size() <= size) {
		Specimen spec(graph);
		specimenSet->insert(spec);
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

	specimenSet->insert(child1);
	specimenSet->insert(child2);

	//child1.print();
	//child2.print();
}

void Population::sortPopulation() {
	//objects.clear();
	objects.assign(specimenSet->begin(),specimenSet->end());
	//objects = *(new vector<Specimen>(specimenSet->begin(),specimenSet->end());
	sort(objects.begin(), objects.end(), Specimen::compare);
}

void Population::scxCrossover() {
	vector<Specimen> offsprings;//(size/4, objects[0]);
	//cout<<"inSCX before for"<<endl;
	for (int i=0; i<size/4; i++) {
	//cout<<"inSCX in for i: "<<i<<endl;
		Specimen a = objects[i];
		Specimen b = objects[rand() % size];
		//cout<<"inSCX in for i: "<<i<<" before scx"<<endl;
		Specimen c = a.scx(b);
		//cout<<"inSCX in for i: "<<i<<" after scx"<<endl;
		//offsprings.at(i) = c;
		offsprings.push_back(c);
	}
	//cout<<"inSCX before insert"<<endl;
	specimenSet->insert(offsprings.begin(),offsprings.end());
	//cout<<"inSCX"<<endl;

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
	specimenSet->insert(offsprings.begin(),offsprings.end());
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
			specimenSet->insert(a);
		}
}

void Population::getNextGeneration() {
	//vector<Specimen> newObjects;
	sortPopulation();
	specimenSet->clear();
	if (objects.size() > size) {
		for (int i=0; i<size; i++) {
			specimenSet->insert(objects[i]);
		}
		//specimenSet->insert(newObjects.begin(),newObjects.end());
	}
}

void Population::merge(Population second) {
	specimenSet->insert(second.specimenSet->begin(),second.specimenSet->end());
	size = specimenSet->size();
}

void Population::evolve() {
	sortPopulation();
	//cout<<"scx"<<endl;
	scxCrossover();
	//cout<<"tpx"<<endl;
	tpxCrossover();
	//cout<<"mutate"<<endl;
	mutate();
	//cout<<"next"<<endl;
	getNextGeneration();
}
