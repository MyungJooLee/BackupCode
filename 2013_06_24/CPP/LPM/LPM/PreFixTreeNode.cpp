#include "PreFixTreeNode.h"


PreFixTreeNode::PreFixTreeNode(void)
{
	// Variable Initialize
	cValueExist = false;
	for(int i=0; i<AlphabetSize; i++)
		ptrNextLevel[i] = NULL;
}

PreFixTreeNode* PreFixTreeNode::getNextLevelNode(char value)
{
	int index = value - 'a';

	if(index >= AlphabetSize || index < 0)
		return NULL;
	else
		return ptrNextLevel[index];
}

bool PreFixTreeNode::setNextLevelNode(string str)
{
	int index = str[0] - 'a';
	if(index >= AlphabetSize || index < 0)
		return false;

	PreFixTreeNode* ptrNextLevelNode = ptrNextLevel[index];
	int Length = 0;

	// if no Exist Tree Node
	if(ptrNextLevelNode == NULL)
	{
		// Make it
		ptrNextLevelNode = new PreFixTreeNode();
		ptrNextLevel[str[0] - 'a'] = ptrNextLevelNode;
	}

	// if Last Ch
	if(str.length() > 1)
	{
		return ptrNextLevelNode->setNextLevelNode(str.substr(1, str.length()-1));
	}
	else
	{
		ptrNextLevelNode->cValueExist = true;
		return true;
	}	
}

PreFixTreeNode::~PreFixTreeNode(void)
{
	// No Job.
}
