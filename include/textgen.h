#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <map>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

typedef deque<string> prefix;

class TextGenerator {
	const int NPREF = 2;
	const int MAXGEN = 1000;
	map<prefix, vector<string>> statetab;
	prefix firstPref;
public:
	const map<prefix, vector<string>>& getStateTable() { return statetab; }
	const prefix& getFirstPrefix() { return firstPref; }
	TextGenerator();
	TextGenerator(ifstream& file);
	TextGenerator(string text);
	string Generate();
};