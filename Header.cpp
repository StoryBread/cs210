/*
Dan Story
CS 210
Project 3
*/

#include "Header.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>			
#include <string>


using namespace std;

// Constructor 
void Groceries::Grocery() {
	fileInput = "CS210_Project_Three_Input_File.txt";  // Assigned the assigned input file
	fileOutput = "frequency.dat";
	name = "";
	quantity = 0;
}

// Constructor with values 
void Groceries::Grocery(string Input, string Output) {
	fileInput = Input;
	fileOutput = Output;
	name = "";
	quantity = 0;
}

// Print menu option 1
void Groceries::MenuOption1() {
	bool exit = false;

	while (!exit) {
		cout << "Please enter a word to search for or [q] to quit... ";
		cin >> name;

		// Check to see that it's valid
		try {
			// check for a number in the search
			for (char a : name) {
				if (!isalpha(a)) {
					throw invalid_argument("Not a valid string. Must enter letters");
				}
			}
			
			// The searched name was found in the map
			if (grocContainer.find(name) != grocContainer.end()) {
				cout << "Found! There are " << grocContainer[name] << " " << name << "." << endl;
			}
			// The searched name was NOT found in the map
			else {
				throw invalid_argument("Could not find any " + name);
			}
		}

		// Displays the error message 
		catch (invalid_argument& e) {
			cout << "**ERROR** - " << e.what() << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');;
			cin.clear();
		}

		// Check to see if the user entered 'q' 
		if (name == "q") {
			exit = true;
		}
		cout << endl;
	}
}

// Print menu option 2
void Groceries::MenuOption2() {

	// Set every name in the map to a 30 length and fill with '.' 
	for (auto iterate = grocContainer.begin(); iterate != grocContainer.end(); ++iterate) {
		cout << left << setw(30) << iterate->first << setfill('.') << iterate->second << endl;
	}
	cout << endl;
}

// Print menu option 3
void Groceries::MenuOption3() {

	// Look at every name in the map and creates a loop to create the correct number of '*' next to it
	for (auto iterate = grocContainer.begin(); iterate != grocContainer.end(); ++iterate) {

		// Print the item name
		cout << iterate->first << " ";

		// Prints the '*' for the number of each grocery item in the map
		for (int i = 0; i < iterate->second; ++i) {
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;
}


// Takes the input file and reads records and outputs it to the the new file
void Groceries::InventoryItem() {
	string tempName;
	ifstream inFS;					// Stands for File Input
	ofstream outFS;					// Stands for File Output

	// Open the Input and Output files
	inFS.open(fileInput);
	outFS.open(fileOutput);

	// Detects if the input file was able to be opened
	// Provides an Error if the input file wasn't opened
	if (!inFS.is_open()) {
		cout << "Could not open file " << fileInput << endl;
		return;
	}

	// Detects if the output file was able to be opened
	// Provides an Error if the output file wasn't opened
	if (!outFS.is_open()) {
		cout << "Could not open file " << fileOutput << endl;
		return;
	}


	// This section take the Input File and reads all of it to a map for temp storage
	while (!inFS.fail()) {
		// Get input file's first line
		getline(inFS, name);


		while (getline(inFS, name)) {
			inFS >> tempName;
			// If the item is already found it adds a quantity to the name
			if (grocContainer.count(tempName)) {
				grocContainer[tempName] += 1;
			}

			// First time the name is entered into the map
			else {
				grocContainer.insert(pair<string, int>(tempName, 1));
			}
		}
	}

	// This section writes to the Output File 
	// This for loop looks at all the tiems in the map and sends them all to the Output File
	for (auto itr = grocContainer.begin(); itr != grocContainer.end(); ++itr) {
		outFS << itr->first << " " << itr->second << endl;
	}

	// Close the Input file
	inFS.close();

	// Close the Output File
	outFS.close();
}