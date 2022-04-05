#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Treey.h"

using namespace std;

struct Book {
	string title;
	string author;
	int wordCount;
	int newLineCount;
};

int fmain(void) {	
	/*
	Treey<tuple<string, int>> wordTree = Treey<tuple<string, int>>();

	/*need to create the tree, nodes contain string and word count
	read through the file
	upon encountering new word, insert new node with word and count=1
	upon encountering familiar word, increment familiar node's count

	string filename;
	ifstream lineFstrstr;
	ifstream wordFstrstr;
	string line;

	do {
		cout << "Enter the name of the file to be processed: ";
		cin >> filename;
		lineFstrstr.open(filename);
		wordFstrstr.open(filename);
		if (lineFstrstr)
			break;
		
		cout << "File does not exist." << endl << endl;
	} while (!lineFstrstr);

	wordFstrstr >> line;
	while (wordFstrstr) {
		//b.wordCount++;
		
		if (find(wordFstrstr, wordFstrstr) == nullptr) {
			insert(wordFstrstr);

		} else {
			find(wordFstrstr)->freq++;
		}

		wordFstrstr >> line;
	}
*/
	return 0;
}

int main(void) {
	Treey<int, int> tree = Treey<int, int>();
	tree.insert(1, 5);
	tree.insert(2, 1);
	tree.insert(3, 1);
	tree.insert(4, 5);
	tree.insert(5, 5);
	tree.insert(6, 5);
	tree.insert(7, 5);
	tree.insert(8, 5);
	tree.insert(9, 5);
	tree.insert(10, 5);
	tree.insert(11, 5);

	system("pause");
	return 0;
}