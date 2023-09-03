//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// Name : Thiago Flores
// Student ID : 150237220
// OOP244NAA

#include <iostream>
#include "Utils.h"

using namespace std;
namespace sdds {
	int correctInput(int minValue, int maxValue, const char* userMessage) {
		int userInput;
		bool correctInput = false;

		while (!correctInput) {
			cin >> userInput;

			if (cin.fail() || userInput < minValue || userInput > maxValue) {
				cout << userMessage;
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else {
				correctInput = true;
			}
		}

		return userInput;
	}
}