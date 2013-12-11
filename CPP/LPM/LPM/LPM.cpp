#include "LPM.h"


LPM::LPM(void)
{
	ptrPreFixTree = new PreFixTree();
}


LPM::~LPM(void)
{
	delete ptrPreFixTree;
}


// Make Prefix-Tree
void LPM::setup(string str[], int length)
{
	for(int i=0; i<length; i++)
	{
		if(ptrPreFixTree->addPreFix(str[i]) == false)
				cout << "\"" << str[i] << "\" is not support! Only use Lower-Case Alphabet" << endl;
	}
}


    // this method should return the longest prefix from the prefix words
string LPM::findLongestPrefix(string theInputWord)
{	
	int PreFixLevel = 0;
	PreFixLevel = ptrPreFixTree->findPrefix(theInputWord);
	if(PreFixLevel < 0)
		return "Not Found";
	return theInputWord.substr(0, PreFixLevel);
}
   
#define StrinArraySize	5
void main()
{
	LPM* ptrLPM = new LPM();
	string str[StrinArraySize] = {"simpleisbest", "a", "abc", "bcd", "abcd"};

	ptrLPM->setup(str, StrinArraySize);


	cout << ptrLPM->findLongestPrefix("abcedfwfwewfwefewfwefewfwef") << endl;
	cout << ptrLPM->findLongestPrefix("abcdefghi") << endl;
	cout << ptrLPM->findLongestPrefix("ab") << endl;

	delete ptrLPM;
}