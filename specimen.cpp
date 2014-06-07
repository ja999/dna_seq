#include "specimen.h"

int Specimen::getNextIndex(int index) {
	return nextIndexes[index];
}

Specimen::Specimen(WordsGraph *graph) : graph(graph), fitness(-1), full_alignment_length(-1) {
	nextIndexes = new int[graph->getSize()];
	vector<int> specimen_indexes;
	for (int i=0; i<graph->getSize(); i++) {
		specimen_indexes.push_back(i);
	}
	random_shuffle(specimen_indexes.begin(), specimen_indexes.end());
	for (int i=0; i<specimen_indexes.size(); i++) {
		nextIndexes[specimen_indexes.at(i)] = specimen_indexes.at((i+1)%specimen_indexes.size());
	}
	start = rand()%graph->getSize();
	//cout<<"SPEC"<<endl;
	//int tmp = start;
	/*
	do {
		cout<<tmp<<" ";
		tmp = nextIndexes[tmp];
	} while (tmp!=start);
	cout<<start<<endl;
	/*
	nextIndexes[0]=0;
	for (int i=1; i<graph->getSize(); i++) {
		nextIndexes[i]=i;
		swap(nextIndexes[i], nextIndexes[rand()%i]);	
	}
	*/
	calculateFitness();
}

Specimen::Specimen(WordsGraph *graph, int * nextIndexes, int start) :
		graph(graph), nextIndexes(nextIndexes), start(start), fitness(-1), full_alignment_length(-1) {
	/*
	int tmp=start;
	do {
		cout<<nextIndexes[tmp]<<" ";
		tmp=nextIndexes[tmp];
	} while (tmp!=start);
	//vector<bool> visited(graph->getSize());
	/*
	queue<int> toFix;
	int tmp = start;
	for (int i=0; i<graph->getSize(); i++) {
		if (!visited.at(tmp)) {
			visited.at(tmp) = true;
			tmp=nextIndexes[tmp];
		}
		else {
			toFix.push(i);
		}
	}
	if(!toFix.empty()) 
		fix(visited, toFix);
		*/
	calculateFitness();
}

Specimen Specimen::scx(Specimen second) {
	int* childNextIndexes = new int[graph->getSize()];
	int childStart;
	vector<bool> visited(graph->getSize());
	int tmp;
	if (rand()%2) {
		childStart = start;
	}
	else {
		childStart = second.start;
	}
	tmp = childStart;
	visited.at(childStart) = true;
	int alfa, beta; //kandydaci na następne słowo z każdego rodzica
	for (int i=0; i<graph->getSize(); i++) {
		alfa = getNextIndex(tmp);
		beta = second.getNextIndex(tmp);
		//cout<<alfa<<" "<<beta<<endl;
		if (visited.at(alfa)) {
			for (int j=0; j<graph->getSize(); j++) {
				if (!visited.at(j)) {
					alfa = j;
					break;
				}
			}
		}
		if (visited.at(beta)) {
			for (int j=0; j<graph->getSize(); j++) {
				if (!visited.at(j)) {
					beta = j;
					break;
				}
			}
		}
		if (graph->getOverlap(tmp, alfa) * (rand()%100) < graph->getOverlap(tmp, beta) * (rand()%100)) {
			visited.at(alfa) = true;
			childNextIndexes[tmp] = alfa;
			tmp = alfa;
		}
		else {
			visited.at(beta) = true;
			childNextIndexes[tmp] = beta;
			tmp = beta;
		}
	}
	//exit(NULL);
	Specimen child(graph,childNextIndexes,childStart);
	return child;
}

void Specimen::fix(vector<bool>& visited, queue<int>& toFix) {
		/*
	queue<int> lost;

	for (int i=0; i<visited.size(); i++) {
		if (!visited[i]) {
			lost.push(i);
		}
	}

	while(!toFix.empty()) {
		nextIndexes[fix.front()] = lost.front();
		nextIndexes[lost.front()] = specimen_indexes.at((toFix.front()+1)%specimen_indexes.size());
		toFix.pop();
		lost.pop();
	}
	*/
}

bool Specimen::validate() {
	vector<bool> visited(graph->getSize());

	for (int i=0; i<graph->getSize(); i++) {
		visited[nextIndexes[i]] = true;
	}

	for (int i=0; i<visited.size(); i++) {
		if (!visited[i]) {
			return false;
		}
	}
	return true;
}

int Specimen::calculateFitness() {
	int word_length = graph->getWord(start).getText().size();
	int length = word_length;
	int result;
	int tmp = start;
	for (int i=1; i<graph->getSize(); i++) {
		length += graph->getOverlap(tmp,nextIndexes[tmp]);
		tmp = nextIndexes[tmp];
		if (length <= graph->getN()) {
			result = i+1;
		}
	}
	//cout<<"len "<<length<<endl;
	full_alignment_length = length;
	fitness = result;
	return result;
}

void Specimen::print() {
	int tmp = start;
	for (int i=0; i<graph->getSize(); i++) {
		cout<<tmp<<' ';
		tmp = nextIndexes[tmp];
	}
	cout<<endl;
	cout<<"Specimen size: "<<graph->getSize()<<endl;
	cout<<"Specimen fitness: "<<fitness<<endl;
	cout<<"Specimen full_alignment_length: "<<full_alignment_length<<endl;
	cout<<"Specimen valid? ";
	if (validate())
		cout<<"true"<<endl;
	else
		cout<<"false"<<endl;
}

void Specimen::printStats() {
	cout<<"Specimen size: "<<graph->getSize()<<endl;
	cout<<"Specimen fitness: "<<fitness<<endl;
	cout<<"Specimen full_alignment_length: "<<full_alignment_length<<endl;
	if(fitness == graph->getSize())
		exit(0);
}

bool Specimen::compare(Specimen a, Specimen b) {
	if (a.fitness == b.fitness) {
		if (a.full_alignment_length == b.full_alignment_length) {
			for (int i=0; i<a.graph->getSize(); i++)
				if(a.nextIndexes[i] != b.nextIndexes[i])
					return a.nextIndexes[i] < b.nextIndexes[i];
			return 0;
		}
		else
			return a.full_alignment_length < b.full_alignment_length;
	}
	else {
		//return a.full_alignment_length < b.full_alignment_length;
		return a.fitness > b.fitness;
	}
}

void Specimen::swapIndexes(int a, int b) {
	if (getNextIndex(a) != b && getNextIndex(b) != a)
		swap(nextIndexes[a], nextIndexes[b]);
}
/*
bool Specimen::compare(Specimen a, Specimen b) {
	if (a.fitness == b.fitness)
		return a.full_alignment_length < b.full_alignment_length;
	else
		return a.fitness > b.fitness;
}
*/
/*
bool Specimen::operator==(const Specimen& other) {
	return specimen_indexes == other.specimen_indexes;
}
*/
