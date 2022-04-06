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

	Treey<string, int> wordTree = Treey<string, int>();

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
		if (wordTree.find(word) == nullptr) {
			

			wordTree.insert(word, 1);
		}
		else {
			(*wordTree.find(word))++;
		}
		strContents.push_back(word);
		Fstrstr >> word;
	}

	std::string buff;
	int choice;
	do
	{
		cout << "Choose an option from below:" << endl;
		cout << "[1] Search for a node" << endl;
		cout << "[2] Get all ascending" << endl;
		cout << "[3] Get all descending" << endl;
		cout << "[4] Exit" << endl;
		
		cin >> choice;
		int* arr = new int[wordTree.numNodes()];
		int j = 0;
		int* a = nullptr;
		switch (choice)
		{
		case 1:
			cout << "Enter a word" << endl;
			cin >> buff;
			a = wordTree.find(buff);
			if (!a)
				cout << "Word does not exist" << endl;
			else
				cout << *a << endl;
			break;
		case 2:
			wordTree.getAllAscending(arr, j, nullptr);
			for (int i = 0; i < wordTree.numNodes(); i++)
				cout << arr[i] << " ";
			cout << endl;

			break;
		case 3:
			wordTree.getAllDescending(arr, j, nullptr);
			for (int i = 0; i < wordTree.numNodes(); i++)
				cout << arr[i] << " ";
			cout << endl;

			break;
		default:
			break;
		}

	} while (choice != 4);
	
	return 0;
}
