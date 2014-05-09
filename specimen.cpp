#include "specimen.h"

int Specimen::getNextIndex(int index) {
	return nextIndexes[index];
}

Specimen::Specimen(WordsGraph *graph) : graph(graph) {
	nextIndexes = new int[graph->getSize()];
	for (int i=0; i<graph->getSize(); i++) {
		specimen_indexes.push_back(i);
	}
	random_shuffle(specimen_indexes.begin(), specimen_indexes.end());
	for (int i=0; i<specimen_indexes.size(); i++) {
		nextIndexes[specimen_indexes.at(i)] = specimen_indexes.at((i+1)%specimen_indexes.size());
	}
	calculateFitness();
}

Specimen::Specimen(WordsGraph *graph, vector<int> specimen_indexes) :
		graph(graph), specimen_indexes(specimen_indexes) {
	nextIndexes = new int[specimen_indexes.size()];
	vector<bool> visited(specimen_indexes.size());
	queue<int> toFix;
	for (int i=0; i<specimen_indexes.size(); i++) {
		if (!visited.at(specimen_indexes.at(i))) {
			visited.at(specimen_indexes.at(i)) = true;
			nextIndexes[specimen_indexes.at(i)] = specimen_indexes.at((i+1)%specimen_indexes.size());
		}
		else {
			toFix.push(i);
		}
	}
	if(!toFix.empty()) 
		fix(visited, toFix);
	calculateFitness();
}

Specimen Specimen::scx(Specimen second) {
	vector<int> child_indexes;
	vector<bool> visited(specimen_indexes.size());
	child_indexes.reserve(specimen_indexes.size());
	if (rand()%2) {
		visited.at(specimen_indexes.at(0)) = true;
		child_indexes.push_back(specimen_indexes.at(0));
	}
	else {
		visited.at(second.specimen_indexes.at(0)) = true;
		child_indexes.push_back(second.specimen_indexes.at(0));
	}
	int alfa, beta; //kandydaci na następne słowo z każdego rodzica
	for (int i=1; i<specimen_indexes.size(); i++) {
		alfa = getNextIndex(child_indexes.back());
		beta = second.getNextIndex(child_indexes.back());
		if (visited.at(alfa)) {
			for (int j=0; j<specimen_indexes.size(); j++) {
				if (!visited.at(j)) {
					alfa = j;
					break;
				}
			}
		}
		if (visited.at(beta)) {
			for (int j=0; j<specimen_indexes.size(); j++) {
				if (!visited.at(j)) {
					beta = j;
					break;
				}
			}
		}
		if (graph->getOverlap(child_indexes.back(), alfa) < graph->getOverlap(child_indexes.back(), beta)) {
			visited.at(alfa) = true;
			child_indexes.push_back(alfa);
		}
		else {
			visited.at(beta) = true;
			child_indexes.push_back(beta);
		}
	}
	Specimen child(graph,child_indexes);
	return child;
}

void Specimen::fix(vector<bool>& visited, queue<int>& toFix) {
	queue<int> lost;

	for (int i=0; i<visited.size(); i++) {
		if (!visited[i]) {
			lost.push(i);
		}
	}

	while(!toFix.empty()) {
		nextIndexes[specimen_indexes.at((specimen_indexes.size()+toFix.front()-1)%specimen_indexes.size())] = lost.front();
		nextIndexes[lost.front()] = specimen_indexes.at((toFix.front()+1)%specimen_indexes.size());
		specimen_indexes[toFix.front()] = lost.front();
		toFix.pop();
		lost.pop();
	}
}

bool Specimen::validate() {
	vector<bool> visited(specimen_indexes.size());

	for (int i=0; i<specimen_indexes.size(); i++) {
		visited[specimen_indexes[i]] = true;
	}

	for (int i=0; i<visited.size(); i++) {
		if (!visited[i]) {
			return false;
		}
	}
	return true;
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
	cout<<"Specimen valid? ";
	if (validate())
		cout<<"true"<<endl;
	else
		cout<<"false"<<endl;
}

void Specimen::printStats() {
	cout<<"Specimen size: "<<specimen_indexes.size()<<endl;
	cout<<"Specimen alignment_length: "<<alignment_length<<endl;
}

bool Specimen::compare(Specimen a, Specimen b) {
	if (a.alignment_length < b.alignment_length)
		return true;
	else
		return false;
}
