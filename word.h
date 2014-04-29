#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "debug.h"
using namespace std;

class Word {
  private:
    static map<char,int> bases;
  	int hash;
  	string text;
  public:
  	Word(string text);
  	int overlap(vector<int> patternHash);
  	vector<int> getPatternHash();
  	string getText();
};

#endif
