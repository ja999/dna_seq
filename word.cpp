#include "word.h"

map<char,int> Word::bases = {
	{'A', 0},
	{'T', 1},
	{'C', 2},
	{'G', 3}
};

Word::Word(string text) {
	this->text = text;
	hash = 0;
	for (int i=0; i<text.size(); i++) {
		hash = hash * 4 + bases[text[i]];
	}
	DEBUG_IF(true) cout<<"hash: "<<hash<<endl;
}

int Word::overlap(vector<int> patternHash) {
	int tmp = hash;
	for (int i=0; i<text.size()-1; i++) {
		tmp = tmp/4;
		DEBUG_IF(true) cout<<"hash: "<<tmp<<" pattern: "<<patternHash[i]<<endl;
		if (patternHash[i] == tmp)
			return 1 + i;
	}
	return text.size();
}

vector<int> Word::getPatternHash() {
	vector<int> result;
	int tmp = 1<<(2*text.size());
	for(int i = 1; i < text.size(); i++) {
		tmp = tmp>>2;
		result.push_back(hash%tmp);
	}
	return result;

}

string Word::getText() {
	return text;
}
