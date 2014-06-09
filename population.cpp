#include "population.h"

Population::Population(WordsGraph *graph) {

  	bool(*fn_pt)(Specimen,Specimen) = Specimen::compare;
	specimenSet = new set<Specimen,bool(*)(Specimen,Specimen)>(fn_pt);
	while (specimenSet->size() <= size) {
		//Specimen spec(graph);
		specimenSet->emplace(graph);
	}
}

void Population::tpx(Specimen first, Specimen second) {
		/*
	int random1 = rand() % first.graph->getSize(),
	random2 = rand() % first.graph->getSize(),
	random3 = rand() % first.graph->getSize();

	vector<int> childIndexes1, childIndexes2;
	vector<int> crossoverPionts;
	crossoverPionts.push_back(0);
	crossoverPionts.push_back(random1);
	crossoverPionts.push_back(random2);
	crossoverPionts.push_back(random3);
	crossoverPionts.push_back(first.graph->getSize());
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
	*/
}

void Population::sortPopulation() {
	objects.clear();
	objects.assign(specimenSet->begin(),specimenSet->end());
	//objects = *(new vector<Specimen>(specimenSet->begin(),specimenSet->end());
	//sort(objects.begin(), objects.end(), Specimen::compare);
}

void Population::scxCrossover() {
	vector<Specimen> offsprings;//(size/4, objects[0]);
	//cout<<"inSCX before for"<<endl;
	for (int i=0; i<size/4; i++) {
	//cout<<"inSCX in for i: "<<i<<endl;
		Specimen a = objects[i];
		Specimen b = objects[rand() % size];
		//cout<<"inSCX in for i: "<<i<<" before scx"<<endl;
		//cout<<"inSCX in for i: "<<i<<" after scx"<<endl;
		//offsprings.at(i) = c;
		offsprings.push_back(a.scx(b));
	}
	//cout<<"inSCX before insert"<<endl;
	//specimenSet->insert(offsprings.begin(),offsprings.end());
	//cout<<"inSCX"<<endl;
	
	for (int i=0; i<size/4; i++) {
		int random = rand() % size;
		int random2 = rand() % size;
		Specimen a = objects[random];
		while (random == random2)
			random2 = rand() % size;
		Specimen b = objects[random2];
		//Specimen c = a.scx(b);
		offsprings.push_back(a.scx(b));
		//offsprings.push_back(c);
	}
	specimenSet->insert(offsprings.begin(),offsprings.end());
	offsprings.clear();
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
			//Specimen a = objects[randomSpecimen].mutate();
			specimenSet->insert(objects[randomSpecimen].mutate());
		}
}

void Population::getNextGeneration() {
	//vector<Specimen> newObjects;
	//cout<<"before clear vector: "<<Specimen::obj<<" set size: "<<specimenSet->size()<<endl;
	//objects.clear();
	//cout<<"before sort: "<<Specimen::obj<<" set size: "<<specimenSet->size()<<endl;
	sortPopulation();
	//cout<<"after sort: "<<Specimen::obj<<" set size: "<<specimenSet->size()<<endl;
	specimenSet->clear();
	//cout<<"after clear set: "<<Specimen::obj<<" set size: "<<specimenSet->size()<<endl;
	for (int i=0; i<objects.size(); i++) {
		if (specimenSet->size() < size) {
			specimenSet->insert(objects[i]);
		}
		//specimenSet->insert(newObjects.begin(),newObjects.end());
	}
	//cout<<"after fill set: "<<Specimen::obj<<" set size: "<<specimenSet->size()<<endl;
	objects.clear();
	//cout<<"after clear vector: "<<Specimen::obj<<" set size: "<<specimenSet->size()<<endl;
}

void Population::merge(Population second) {
	specimenSet->insert(second.specimenSet->begin(),second.specimenSet->end());
	size = specimenSet->size();
	second.objects.clear();
	second.specimenSet->clear();
}

void Population::evolve() {
	//cout<<"sortPopulation"<<endl;
	sortPopulation();
	//cout<<"scx"<<endl;
	scxCrossover();
	//cout<<"tpx"<<endl;
	//tpxCrossover();
	//cout<<"mutate"<<endl;
	mutate();
	//cout<<"next"<<endl;
	getNextGeneration();
}
