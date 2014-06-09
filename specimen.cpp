#include "specimen.h"
int Specimen::obj=0;
bool Specimen::clear=false;

int Specimen::getNextIndex(int index) {
	return nextIndexes[index];
}

Specimen::Specimen(WordsGraph *graph) : graph(graph), fitness(-1), full_alignment_length(-1) {
		obj++;
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
	calculateFitness();
	DEBUG_IF (!validate()) {
		cout<<"gr"<<endl;
		exit(0);
	}
}

Specimen::Specimen(WordsGraph *graph, int * nextIndexes, int start) :
		graph(graph), start(start), fitness(-1), full_alignment_length(-1) {
		obj++;
	this->nextIndexes = new int[graph->getSize()];
	copy(nextIndexes, nextIndexes + graph->getSize(), this->nextIndexes);
	calculateFitness();
}

Specimen::Specimen(const Specimen& other) :
		graph(other.graph), start(other.start), fitness(other.fitness), full_alignment_length(other.full_alignment_length) {
		obj++;
	nextIndexes = new int[graph->getSize()];
	copy(other.nextIndexes, other.nextIndexes + graph->getSize(), nextIndexes);
	DEBUG_IF (!validate()) {
		cout<<"copy"<<endl;
		exit(0);
	}
}

Specimen& Specimen::operator=(const Specimen& other) {
	if (this != &other) {
		//obj++;
		start = other.start;
		graph = other.graph;
		fitness = other.fitness;
		full_alignment_length = other.full_alignment_length;
		delete[]nextIndexes;
		nextIndexes = new int[graph->getSize()];
		copy(other.nextIndexes, other.nextIndexes + graph->getSize(), nextIndexes);
		DEBUG_IF (!validate()) {
			cout<<"operator"<<endl;
			exit(0);
		}
	}
	return *this;
}


Specimen::~Specimen() {
	delete[] nextIndexes;
	obj--;
	if(clear)
		cout<<obj<<" ";
}
/*
*/
Specimen Specimen::mutate() {
	int randomWord1 = rand() % graph->getSize();
	int randomWord2 = rand() % graph->getSize();
	Specimen mutant(graph, nextIndexes, start);
	mutant.swapWords(randomWord1,randomWord2);
	DEBUG_IF (!mutant.validate()) {
		cout<<"mutacja"<<endl;
		exit(0);
	}
	return mutant;
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
	for (int i=1; i<graph->getSize(); i++) {
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
		//cout<<alfa<<" "<<visited.at(alfa)<<" "<<beta<<" "<<visited.at(beta)<<endl;
		//if (graph->getOverlap(tmp, alfa) < graph->getOverlap(tmp, beta)) {
		if ((graph->getOverlap(tmp, alfa) + graph->getOverlap(alfa, nextIndexes[alfa])/2) * ((100-SCX_PROBABILITY) + rand()%SCX_PROBABILITY) < (graph->getOverlap(tmp, beta) + graph->getOverlap(beta, nextIndexes[beta])/2) * ((100-SCX_PROBABILITY) + rand()%SCX_PROBABILITY)) {
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
	childNextIndexes[tmp] = childStart;
	//exit(NULL);
	Specimen child(graph,childNextIndexes,childStart);
	DEBUG_IF (!child.validate()) {
				cout<<"scx"<<endl;
				exit(0);
			}
	delete[] childNextIndexes;
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

bool Specimen::validate() const{
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

void Specimen::print() const{
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

void Specimen::printStats() const {
	cout<<"Specimen size: "<<graph->getSize()<<endl;
	cout<<"Specimen fitness: "<<fitness<<endl;
	cout<<"Specimen full_alignment_length: "<<full_alignment_length<<endl;
	if(fitness == graph->getSize()) {
		this->print();
		exit(0);
	}
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

void Specimen::swapWords(int a, int b) {
	if (nextIndexes[a] == start)
		start = nextIndexes[b];
	else if (nextIndexes[b] == start)
		start = nextIndexes[a];
	swap(nextIndexes[a], nextIndexes[b]);
	swap(nextIndexes[nextIndexes[a]], nextIndexes[nextIndexes[b]]);
	calculateFitness();
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
