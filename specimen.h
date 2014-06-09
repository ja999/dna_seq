#ifndef SPECIMEN_H
#define SPECIMEN_H

#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <queue>
#include "wordsGraph.h"
#include "parameters.h"

using namespace std;

class Specimen {
	private:
		int* nextIndexes;
		int getNextIndex(int index);
		void fix(vector<bool>& visited, queue<int>& toFix);
		int fitness;
		int full_alignment_length;
		int start;
	public:
		static int obj;
		static bool clear;
		WordsGraph *graph;
		Specimen(WordsGraph *graph);
		Specimen(WordsGraph *graph, int* nextIndexes, int start);
		Specimen(const Specimen& other);
		Specimen& operator=(const Specimen& other);
		~Specimen();
		static Specimen random(WordsGraph *graph);
		Specimen scx(Specimen second);
		//vector<int> specimen_indexes;
		string specimen_aligned = "";
		static bool compare(Specimen a, Specimen b);
		//bool Specimen::operator==(const Specimen& other);
		int calculateFitness();
		bool validate() const;
		void print() const;
		void printStats() const;
		void swapWords(int a, int b);
		Specimen mutate();
		//static bool(*compare_pt)(Specimen,Specimen) = Specimen::compare;
};

#endif
