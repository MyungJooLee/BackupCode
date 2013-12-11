#pragma once
#include <string>
#include <iostream>

using namespace std;

#include "PreFixTree.h"

class LPM
{
public:
	LPM(void);
	~LPM(void);
	
	void setup(string s[], int length);
	string findLongestPrefix(string theInputWord);
private:
	PreFixTree* ptrPreFixTree;
};

