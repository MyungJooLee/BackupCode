#pragma once

#include <string>

using namespace std;

#include "PreFixTreeNode.h"


class PreFixTree
{
public:
	PreFixTree(void);
	~PreFixTree(void);

	bool addPreFix(string str);
	int findPrefix(string str);

	PreFixTreeNode* ptrRootNode;
};

