#pragma once

#include <string>

using namespace std;

// Only Small Alphabet => 26
#define AlphabetSize	26
#define NULL 0
class PreFixTreeNode
{
public:
	PreFixTreeNode(void);
	~PreFixTreeNode(void);

	PreFixTreeNode* getNextLevelNode(char value);
	bool setNextLevelNode(string str);
	bool cValueExist;

private:
	
	PreFixTreeNode* ptrNextLevel[AlphabetSize];
};

