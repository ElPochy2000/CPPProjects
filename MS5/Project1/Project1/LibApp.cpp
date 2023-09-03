//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// Name : Thiago Flores
// Student ID : 150237220
// OOP244NAA
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "LibApp.h"
#include "Menu.h"
#include "Book.h"
#include "PublicationSelector.h"
#include "Utils.h"

using namespace std;

namespace sdds {
	LibApp::LibApp(const char* fileName) : m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_publicationType("Choose the type of publication:") {
		if (fileName) {
			strcpy(m_fileName, fileName);
		}

		m_changed = false;
		m_NOLP = 0;

		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu" ;
		m_publicationType << "Book" << "Publication";
		load();
	}

	bool LibApp::confirm(const char* message) {
		Menu confirm(message);
		confirm << "Yes";
		return confirm.run() == 1;
	}

	LibApp::~LibApp() {
		for (int i = 0; i < m_NOLP; i++) {
			delete m_PPA[i];
		}
	}

	void LibApp::load() {
		char type{};

		cout << "Loading Data" << endl;

		ifstream file(m_fileName);

		for (int i = 0; file && i < SDDS_LIBRARY_CAPACITY; i++) {
			// we first check the type and ignore the whitespace
			file >> type;
			file.ignore();


			// if read succesfully we add a pointer to the array and we declare it as either a publication or a book
			if (file) {
				if (type == 'P') {
					m_PPA[i] = new Publication;
					file >> *m_PPA[i];
					m_NOLP++;
					m_LLRN = m_PPA[i]->getRef();
				}
				else if (type == 'B') {
					m_PPA[i] = new Book;
					file >> *m_PPA[i];
					m_NOLP++;
					m_LLRN = m_PPA[i]->getRef();
				}
			}
		}
	}

	void LibApp::save() {
		cout << "Saving Data" << endl;

		ofstream file(m_fileName);

		//We modify the file and save the new data inside of it
		for (int i = 0; i < m_NOLP; i++) {
			if (m_PPA[i]->getRef() != 0) {
				file << *m_PPA[i] << endl;
			}
		}

		file.close();
	}

	int LibApp::search(int searchType) {
		char userTitle[SDDS_MAX_ARRAY_LEN + 1]{};
		int userInput = 0;
		int libRef = 0;
		char userChar{};
		PublicationSelector publSel("Select one of the following found matches:",15);


		userInput = m_publicationType.run();
		cin.ignore(1000, '\n');

		std::cout << "Publication Title: ";
		cin.getline(userTitle, 256);


		if (userInput == 1) {
			userChar = 'B';
		}
		else if (userInput == 2){
			userChar = 'P';
		}


		// searchType is not selected by the user directly but by other functions calling this function
		// according to the search type we will add the different objects to publsel
		// 1 adds all publications
		// 2 adds only loaned items
		// 3 adds only unloaded items
		if (searchType == 1) {
			for (int i = 0; i < m_NOLP; i++) {
				if (m_PPA[i]->operator==(userTitle) && userChar == m_PPA[i]->type() && m_PPA[i]->getRef() != 0) {
					publSel << m_PPA[i];
				}
			}
		}
		else if (searchType == 2) {
			for (int i = 0; i < m_NOLP; i++) {
				if (m_PPA[i]->operator==(userTitle) && userChar == m_PPA[i]->type() && m_PPA[i]->getRef() != 0 && m_PPA[i] -> onLoan()) {
					publSel << m_PPA[i];
				}
			}
		}
		else if (searchType == 3) {
			for (int i = 0; i < m_NOLP; i++) {
				if (m_PPA[i]->operator==(userTitle) && userChar == m_PPA[i]->type() && m_PPA[i]->getRef() != 0 && !m_PPA[i]->onLoan()) {
					publSel << m_PPA[i];
				}
			}
		}

		// if an item was added to the object we would run it and allow the user to select one of them to action it
		if (publSel) {
			publSel.sort();
			libRef = publSel.run();

			if (libRef > 0) {
				cout << *getPub(libRef) << endl;
			}
			else {
				cout << "Aborted!" << endl;
			}
		}
		else {
			cout << "No matches found!" << endl;
		}


		return libRef;
	}

	void LibApp::returnPub() {
		int libRef = 0;
		int loanedDays = 0;
		double penalty = 0.0;

		cout << "Return publication to the library" << endl;
		libRef = search(2);

		if (libRef > 0) {
			if (confirm("Return Publication?")) {
				// we calculate the checkoutDate with the current one to know if a penalty should be charged
				loanedDays = Date() - getPub(libRef) -> checkoutDate();

				// we calculate the penalty if necessary
				if (loanedDays > SDDS_MAX_LOAN_DAYS) {
					penalty = (loanedDays - SDDS_MAX_LOAN_DAYS) * 0.5;

					cout << fixed;
					cout.precision(2);
					cout << "Please pay $" << penalty << " penalty for being " << (loanedDays - SDDS_MAX_LOAN_DAYS) << " days late!" << endl;
				}

				//as the item is returned we set the membership number as 0
				getPub(libRef)->set(0);
				m_changed = true;

				cout << "Publication returned" << endl;
			}
		}

		cout << endl;
	}

	void LibApp::newPublication() {
		Publication* publications = nullptr;
		int publType = 0;

		// we make sure we are not exceeding the maximun library capacity
		if (m_NOLP == SDDS_LIBRARY_CAPACITY) {
			cout << "Library is at its maximum capacity!" << endl;
		}
		else {
			cout << "Adding new publication to the library" << endl;

			publType = m_publicationType.run();
			cin.ignore(1000, '\n');
			
			if (publType == 0) {
				cout << "Aborted!" << endl;
			}
			else if (publType == 1) {
				publications = new Book;
				cin >> *publications;
			} 
			else if (publType == 2) {
				publications = new Publication;
				cin >> *publications;
			}


			if (cin.fail()) {
				cin.ignore(1000, '\n');
				cin.clear();
				cout << "Aborted!" << endl;
			}
			else if (publType != 0){
				if (!confirm("Add this publication to the library?")) {
					if (!*publications) {
						cout << "Failed to add publication!" << endl;
						delete publications;
					}
				}
				else {
					m_LLRN++;
					publications->setRef(m_LLRN);
					m_PPA[m_NOLP] = publications;
					m_NOLP++;
					m_changed = true;

					cout << "Publication added" << endl;
				}
			}
		}

		cout << endl;
	}

	void LibApp::removePublication() {
		int libRef = 0;

		cout << "Removing publication from the library" << endl;
		libRef = search(1);

		if (libRef) {
			if (confirm("Remove this publication from the library?")) {
				getPub(libRef)->setRef(0);

				m_changed = true;
				cout << "Publication removed" << endl;
			}
		}

		cout << endl;
	}

	void LibApp::checkOutPub() {
		int libRef = 0;
		int userInput = 0;

		cout << "Checkout publication from the library" << endl;
		libRef = search(3);

		if (libRef > 0) {
			if (confirm("Check out publication?")) {
				cout << "Enter Membership number: ";
				userInput = correctInput(10000, 99999, "Invalid membership number, try again: ");

				getPub(libRef)->set(userInput);

				m_changed = true;
				cout << "Publication checked out" << endl;
			}
		}

		cout << endl;
	}

	void LibApp::run() {
		// we will use this bool as an "escape" from the while loop
		bool exit = false;

		do {
			switch (m_mainMenu.run()) {

				// if case 0 is chosen we will start the exit menu
				case 0:
					// before running the menu we will make sure that something was changed by the user. If not we will directly exit the program
					if (m_changed == true) {
						switch (m_exitMenu.run()) {
							case 0:
								if (confirm("This will discard all the changes are you sure?")) {
									exit = true;
								}
								break;
							case 1:
								save();
								exit = true;
								break;
							// if option number 2 is chosen the user decided to continue with the program. As a result it will continue running
							case 2:
								break;
						}
					}
					else {
						exit = true;
					}
					cout << endl;
					break;

				case 1:
					newPublication();
					break;

				case 2:
					removePublication();
					break;

				case 3:
					checkOutPub();
					break;

				case 4:
					returnPub();
					break;
			}
		} while (!exit);

		cout << "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;
	}

	Publication* LibApp::getPub(int libRef) {
		Publication* publications = nullptr;

		for (int i = 0; i < m_NOLP; i++) {
			if (m_PPA[i]->getRef() == libRef) {
				publications = m_PPA[i];
			}
		}

		return publications;
	}
}
