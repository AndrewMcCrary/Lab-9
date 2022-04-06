#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Treey.h"

using namespace std;

struct Book {
	string title;
	string author;
	int wordCount;
	int newLineCount;
};

int main(void) {	

	Treey<string, int>* wordTree = new Treey<string, int>();

	/*
	need to create the tree, nodes contain string and word count
	read through the file
	upon encountering new word, insert new node with word and count=1
	upon encountering familiar word, increment familiar node's count
	*/

	string filename;
	ifstream Fstrstr;
	string word;
	vector<string> strContents;
	string chars = ".,-!#*();:";

	// continually prompts the user to enter an existing file name
	do {
		cout << "Enter the name of the file to be processed: ";
		cin >> filename;
		Fstrstr.open(filename);
		if (Fstrstr)
			break;
		
		cout << "File does not exist." << endl << endl;
	} while (!Fstrstr);

	// comment the following block out to read EVERY word in the file
	// leave uncommented if using the files from HW1 (skips to the contents)
	while (getline(Fstrstr, word)) {
		if (word.compare(0, 8, "Contents") == 0)
			break;
	}

	Fstrstr >> word;
	while (Fstrstr) {
		for (char c : chars) {
			word.erase(std::remove(word.begin(), word.end(), c), word.end());
		}
		//cout << word << endl;
		if (wordTree->find(word) == nullptr) {
			wordTree->insert(word, 1);
		}
		else {
			
		}
		strContents.push_back(word);
		Fstrstr >> word;
	}

	int x = 3;
	do
	{
		cout << "hi" << endl;
		x--;

	} while (x > 0);
	

	//wordFstrstr >> line;
	//while (wordFstrstr) {
	//	//b.wordCount++;
	//	
	//	if (find(wordFstrstr, wordFstrstr) == nullptr) {
	//		insert(wordFstrstr);

	//	} else {
	//		find(wordFstrstr)->freq++;
	//	}

	//	wordFstrstr >> line;
	//}

	return 0;
}
