/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
//	TODO add necessary includes here
//============================================================================
#include "constants.h"
#include "utilities.h"
#include "array_functions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace constants;
//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur

struct entry {
	std::string word;
	int number_occurences;
};

entry words[MAX_WORDS];

int nextAvailable = 0;

//TODO add a global array of entry structs (global to this file)

//TODO add variable to keep track of next available slot in array

//TODO define all functions in header file
bool openFile(std::fstream &myfile, const std::string &myFileName,
		std::ios_base::openmode mode) {
	myfile.open(myFileName.c_str());
	return myfile.is_open();
}
void closeFile(std::fstream &myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}

}
int writeArraytoFile(const std::string &outputfilename) {
	ofstream myfile;
	myfile.open(outputfilename.c_str());
	if (getArraySize() == 0) {
		return FAIL_NO_ARRAY_DATA;
	}
	if (!myfile.is_open()) {
		return FAIL_FILE_DID_NOT_OPEN;
	}

	for (int i = 0; i < getArraySize(); i++) {
		myfile << words[i].word + " " + intToString(words[i].number_occurences)
				<< endl;
	}
	myfile.close();
	return SUCCESS;
}
void sortArray(constants::sortOrder so) {
	switch (so) {
	case constants::ASCENDING: {
		entry temp;
		for (int i = 0; i < nextAvailable - 1; i++) {

			for (int j = i + 1; j < nextAvailable; j++) {
				std::string w2 = words[j].word;
				std::string w1 = words[i].word;

				toUpper(w1);
				toUpper(w2);
				if (w1 > w2) {

					temp = words[i];
					words[i] = words[j];
					words[j] = temp;

				}
			}
		}
		break;
	}
	case constants::NONE:
		break;
	case constants::DESCENDING:
		break;
	case constants::NUMBER_OCCURRENCES:
		break;
	}

}
void clearArray() {
	nextAvailable = 0;
}

int getArraySize() {
	return nextAvailable;
}
void processToken(std::string &token) {
	if (!strip_unwanted_chars(token)) {
		return;
	}

	for (int i = 0; i < nextAvailable; i++) {
		std::string x = words[i].word;
		std::string t = token;
		toUpper(t);
		toUpper(x);
		if (x == t) {
			words[i].number_occurences++;
			return;
		}

	}

	if (token.length() != 0) {
		words[nextAvailable] = entry();
		words[nextAvailable].number_occurences = 1;
		words[nextAvailable].word = token;
		nextAvailable++;
	}

}

void processLine(std::string &myString) {
	stringstream ss(myString);
	string tempToken;
	while (getline(ss, tempToken, CHAR_TO_SEARCH_FOR)) {
		processToken(tempToken);
	}

}
bool processFile(std::fstream &myfstream) {
	std::string line;
	if (!myfstream.is_open()) {
		return false;
	}
	while (!myfstream.eof()) {
		getline(myfstream, line);
		processLine(line);

	}
	return true;
}
int getArrayWord_NumbOccur_At(int i) {
	return words[i].number_occurences;
}
std::string getArrayWordAt(int i) {
	return words[i].word;
}

//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!
