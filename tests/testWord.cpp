#include<iostream>
#include "../word.h"
#include "../debug.h"
using namespace std;
int main () {
#ifdef DEBUG
	cout<<"DEBUG ON"<<endl;
#endif
	while(1) {
		string first;
		string second;
		cin>>first>>second;
		Word firstWord(first);
		Word secondWord(second);
		cout<<firstWord.overlap(secondWord.getPatternHash())<<endl;
	}
	return 0;
}
