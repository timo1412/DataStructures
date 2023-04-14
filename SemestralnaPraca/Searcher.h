#pragma once
#include <vector>

#include "UzemnyCelok.h"
using namespace std;
class Searcher
{
private:
	vector<UzemnyCelok> kraje;
	vector<UzemnyCelok> okresy;
	vector<UzemnyCelok> obce;
	vector<UzemnyCelok> result;
public:
	Searcher(vector<UzemnyCelok> p_kraje, vector<UzemnyCelok> p_okresy, vector<UzemnyCelok> p_obce):
	kraje(p_kraje),okresy(p_okresy),obce(p_obce){}
	void startsWithString(string startString);
	void containsString(string containsString);
	void printResult();
};

