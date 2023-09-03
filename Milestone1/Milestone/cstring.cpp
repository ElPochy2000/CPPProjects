//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// Name : Thiago Flores
// Student ID : 150237220
// OOP244NAA


#include "cstring.h"

namespace sdds {

	void strCpy(char* des, const char* src) {
		if (des != nullptr) {

			for (int i = 0; i < strLen(src); i++) {
				des[i] = src[i];
			}
			des[strLen(src)] = '\0';
		}
	}


	void strnCpy(char* des, const char* src, int len) {
		if (des != nullptr) {
			if (len > strLen(src)) {
				strCpy(des, src);
			}
			else {
				for (int i = 0; i < len; i++) {
					des[i] = src[i];
				}
			}
		}
	}



	int strCmp(const char* s1, const char* s2) {
		//this int will check which string is shorter for running the compare
		int shortString = 0;
		int diffFound = 0; // this will be used to check if strings are different at the end of the loop

		//we check what string is the shortest to compare
		if (strLen(s1) >= strLen(s2)) {
			shortString = strLen(s1);
		}
		else if (strLen(s1) < strLen(s2)) {
			shortString = strLen(s2);
		}

		for (int i = 0; i < shortString; i++) {

			if (s1[i] == s2[i]) {
				;
			}
			else if (s1[i] > s2[i]) {
				diffFound = 1;
				i = shortString; // breaks loop as the first difference has already been found
			}
			else {
				diffFound = -1;
				i = shortString; // breaks loop as the first difference has already been found
			}
		}
		return diffFound;
	}



	int strnCmp(const char* s1, const char* s2, int len) {
		//this int will check which string is shorter for running the compare

		int diffFound = 0; // this will be used to check if strings are different at the end of the loop


		for (int i = 0; i < len; i++) {

			if (s1[i] == s2[i]) {
				;
			}
			else if (s1[i] > s2[i]) {
				diffFound = 1;
				i = len; // breaks loop as the first difference has already been found
			}
			else {
				diffFound = -1;
				i = len; // breaks loop as the first difference has already been found
			}
		}
		return diffFound;
	}



	int strLen(const char* s) {
		// we analize the posibility of a null pointer too
		if (s == nullptr) {
			return 0;
		}

		int len = 0;

		//while the string doesn't end the length will increase
		while (s[len] != '\0') {
			len++;
		}

		return len;
	}



	const char* strStr(const char* str1, const char* str2) {
		int matchFound = 0;

		for (int i = 0; i < strLen(str1); i++) {
			matchFound = 0;  //as we restart the loop we reassign the value of the matches found to 0

			if (str1[i] == str2[0]) {       //potential match is found

				for (int j = 0; j < strLen(str2); j++) {  //loop to check every character of str2 and compare it to our str1
					if (str1[i + j] == str2[j]) {  //if it matches we add one to match found
						matchFound++;

						if (matchFound == strLen(str2)) { // if the amount found is equal to the length of the str2 means that it matches completly
							return &str1[i];  // we return the address of the string found and break the loop
						}
					}

				}
			}
			if (matchFound == strLen(str2)) { break; }  // we check if we found the result desired and if it happens we break the loop
		}
		return nullptr; // if we didn't find a match we return the null pointer
	}



	void strCat(char* des, const char* src) {
		int desLen = strLen(des);
		int srcLen = strLen(src);

		for (int i = 0; i < srcLen; i++) {
			des[desLen + i] = src[i];
		}
		des[desLen + srcLen] = '\0';
	}

}