//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// Name : Thiago Flores
// Student ID : 150237220
// OOP244NAA
#include "LibApp.h"
#include "Menu.h"

using namespace std;

namespace sdds {
	LibApp::LibApp() : m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?") {
		m_changed = false;
		
		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu" ;

		load();
	}

	bool LibApp::confirm(const char* message) {
		Menu confirm(message);
		confirm << "Yes";
		return confirm.run() == 1;
	}

	void LibApp::load() {
		cout << "Loading Data" << endl;
	}

	void LibApp::save() {
		cout << "Saving Data" << endl;
	}

	void LibApp::search() {
		cout << "Searching for publication" << endl;
	}

	void LibApp::returnPub() {
		search();
		cout << "Returning publication" << endl;
		cout << "Publication returned" << endl;
		m_changed = true;
		cout << endl;
	}

	void LibApp::newPublication() {

		cout << "Adding new publication to library" << endl;
		if (confirm("Add this publication to library?")) {
			m_changed = true;
			cout << "Publication added" << endl;
		}

		cout << endl;
	}

	void LibApp::removePublication() {
		cout << "Removing publication from library" << endl;
		search();
		if (confirm("Remove this publication from the library?")) {
			m_changed = true;
			cout << "Publication removed" << endl;
		}
		cout << endl;
	}

	void LibApp::checkOutPub() {
		search();
		if (confirm("Check out publication?")) {
			m_changed = true;
			cout << "Publication checked out" << endl;
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
}
