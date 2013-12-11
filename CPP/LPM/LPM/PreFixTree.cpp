#include "PreFixTree.h"


PreFixTree::PreFixTree(void)
{
	// Variable Initialize
	ptrRootNode = new PreFixTreeNode();
}

bool PreFixTree::addPreFix(string str)
{
	// Add Prefix Tree
	return ptrRootNode->setNextLevelNode(str);
}

int PreFixTree::findPrefix(string str)
{
	int Level = 0;
	int ExistLevel = -1;
	
	PreFixTreeNode* ptrTemp = ptrRootNode;
	while(1)
	{		
		//  LPM Check
		if(ptrTemp->cValueExist == true)
		{
			ExistLevel = Level;
		}

		// Find Next Level
		ptrTemp = ptrTemp->getNextLevelNode(str[Level]);

		// if no Exist
		if(ptrTemp == NULL)
		{
			return ExistLevel;
		}		
		Level++;

		// if String Size is smaller than Current Level
		if(Level >= str.length())
			return ExistLevel;
	}
	return Level;
}


PreFixTree::~PreFixTree(void)
{
	//Variable Deinitialize
	delete ptrRootNode;
}
