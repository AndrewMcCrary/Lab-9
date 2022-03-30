///
/// Group Members:
/// Andrew McCrary
/// Ricky Roberts
/// Vitta Silberberg
///
/// Instructions:
/// Build the vs project, and run
/// 
/// All contributions are equal.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

const string LALPHA = "abcdefghijklmnopqrstuvwxyz";
const string UALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct Book {
	string title;
	string author;
	int wordCount;
	int letterFreq[26];
	int newLineCount;
	int letters;
};

int main(void) {
	string buff = "";

	do {
		string filename;
		ifstream lineFstrstr;
		ifstream wordFstrstr;
		string line;
		vector<string> lineContents;
		vector<string> strContents;

		do {
			cout << "Enter the name of the file to be processed: ";
			cin >> filename;
			try {
				lineFstrstr.open(filename);
				wordFstrstr.open(filename);
				if (lineFstrstr)
					break;
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			cout << "File does not exist." << endl << endl;
		} while (!lineFstrstr);

		Book b;
		b.wordCount = 0;
		b.newLineCount = 0;

		getline(lineFstrstr, line);
		b.title = line;

		getline(lineFstrstr, line);
		b.author = line;

		while (getline(lineFstrstr, line)) {
			if (line.compare(0, 8, "Contents") == 0)
				break;
		}

		while (getline(wordFstrstr, line)) {
			if (line.compare(0, 8, "Contents") == 0)
				break;
		}

		getline(lineFstrstr, line);
		while (lineFstrstr) {
			b.newLineCount++;
			lineContents.push_back(line);
			getline(lineFstrstr, line);
		}

		wordFstrstr >> line;
		while (wordFstrstr) {
			b.wordCount++;
			strContents.push_back(line);
			wordFstrstr >> line;
		}

		// Save the info in cardcatalog.txt
		ofstream output("CardCatalog.txt", std::ios_base::app | std::ios_base::out);
		output << "Title: " << b.title << endl;
		output << "Full Author: " << b.author << endl;

		int pos = b.author.find(' ');
		output << "Author First Name: " << b.author.substr(0, pos) << endl;
		output << "Author Last Name: " << b.author.substr(pos + 1, b.author.size()) << endl;

		output << "Word Count: " << b.wordCount << endl;
		output << "Line Count: " << b.newLineCount << endl << endl;

		cout << lineContents.size() << endl;
		cout << strContents.size() << endl;

		for (int i = 0; i < sizeof(b.letterFreq) / sizeof(int); i++) {
			b.letterFreq[i] = 0;
		}

		for (int i = 0; i < strContents.size(); i++) {
			for (int j = 0; j < strContents[i].size(); j++) {
				b.letterFreq[LALPHA.find(tolower(strContents[i][j]))]++;
			}
		}

		int totalLetters = 0;
		for (int i = 0; i < sizeof(b.letterFreq) / sizeof(int); i++) {
			totalLetters += b.letterFreq[i];
		}

		cout << "Would you like to display the letter frequency? y/n" << endl;
		cin >> buff;
		if (buff == "y") {
			for (int i = 0; i < sizeof(b.letterFreq) / sizeof(int); i++) {
				cout << LALPHA[i] << ": " << float(b.letterFreq[i]) / totalLetters * 100 << "%" << endl;
			}
		}

		cout << "Would you like to process another book? y/n" << endl;
		cin >> buff;
	} while (buff == "y");

	system("pause");
	return 0;
}