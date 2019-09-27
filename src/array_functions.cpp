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
#include <vector>

using namespace std;
using namespace constants;
//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur
const std::string MYFILE = TEST_DATA_FULL;


struct entry {
	string word;
	int number_occurences;
};

entry words [MAX_WORDS];

int nextAvailable = 0;

//TODO add a global array of entry structs (global to this file)

//TODO add variable to keep track of next available slot in array

//TODO define all functions in header file
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode){
	myfile.open(myFileName.c_str(), mode);
	return false;
}
void closeFile(std::fstream& myfile){
	if (myfile.is_open()){
		myfile.close();
	}

}
int writeArraytoFile(const std::string &outputfilename){
	ofstream myfile;
	myfile.open(outputfilename);
	for(int i = 0; i < nextAvailable; i++){
		myfile << words[i].word;
	}
	myfile.close();
	return 0;
}
void sortArray(constants::sortOrder so){
	switch (so) {
	case constants::ASCENDING:
		for(int i = 0; i<nextAvailable; i++) {
		      int swaps = 0;
		      for(int j = 0; j<nextAvailable-i-1; j++) {
		         if(words[j].word > words[j+1].word) {
		        	entry temp;
		        	temp.word = words[j].word;
		        	words[j].word = words[j+1].word;
		        	words[j+1].word = temp.word;
		            swaps = 1;
		         }
		      }
		      if(!swaps)
		         break;
		   }
		break;

		case constants::NONE:
			break;
		case constants::DESCENDING:
			break;
		case constants::NUMBER_OCCURRENCES:
			break;
	}


}
void clearArray(){
	nextAvailable = 0;
}

int getArraySize(){
	return nextAvailable;
}
void processToken(std::string &token){
	if (strip_unwanted_chars(token)) {
		for (int i = nextAvailable - 1; i < nextAvailable; i++){
			if(words[i].word == token){
				words[i].number_occurences++;
			}
			else {
				entry a;
				a.word = token;
				a.number_occurences = 1;
				words[nextAvailable] = a;
				std::cout<<nextAvailable;
				nextAvailable++;

			}
		}
	}


	}


void processLine(std::string &myString){
	nextAvailable = 0;
	stringstream ss(myString);
	cout<<myString;
	string tempToken;
	while(getline(ss, tempToken, CHAR_TO_SEARCH_FOR)){
		processToken(tempToken);
	}

}
bool processFile(std::fstream &myfstream){
	openFile(myfstream, MYFILE, ios::in);
	std::string line;
	if (!myfstream.is_open()){
		return false;
	}
	while (!myfstream.eof()) {
		processLine(line);

		}
	return true;
}
int getArrayWord_NumbOccur_At(int i){
	return words[i].number_occurences;
}
std::string getArrayWordAt(int i){
	return words[i].word;
}

//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!
