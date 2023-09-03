//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// Name : Thiago Flores
// Student ID : 150237220
// OOP244NAA

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"

namespace sdds {
	MenuItem::MenuItem() {

		m_menuContent = nullptr;
	}


	MenuItem::MenuItem(const char* menuContent) {
		
		if (strlen(menuContent) > 0) {
			m_menuContent = new char[strlen(menuContent) + 1];
			strcpy(m_menuContent, menuContent);
		} else {
			m_menuContent = nullptr;
		}
	}


	MenuItem::~MenuItem() {
		delete[] m_menuContent;
	}


	MenuItem::operator bool()const {
		bool result = false;

		if (m_menuContent != nullptr && m_menuContent) {
			result = true;
		}

		return result;
	}


	MenuItem::operator char* ()const {
		return m_menuContent;
	}


	std::ostream& MenuItem::display(std::ostream& os)const {
		if (*this) {
			os << m_menuContent;
		}

		return os;
	}


	Menu::Menu() {
		menuPointers = 0;
	}


	//This will call the constructor of MenuItem with the menuContent Char
	Menu::Menu(const char* menuContent) : title(menuContent) {};


	Menu::~Menu(){
		unsigned int i;
		
		for (i = 0; i < MAX_MENU_ITEMS; i++) {
			delete  items[i];
		}
	}


	std::ostream& Menu::displayTitle(std::ostream& os) {
		if (title) {
			title.display();
		}

		return os;
	}


	std::ostream& Menu::displayMenu(std::ostream& os) {
		unsigned int i;

		if (title) {
			title.display();
			os << std::endl;
		}

		for (i = 0; i < menuPointers; i++) {
			os.width(2);
			os.fill(' ');
			os.setf(std::ios::right);
			os << i + 1 << "- ";

			os.unsetf(std::ios::right);
			os.setf(std::ios::left);

			items[i]->display(os);
			os << std::endl;
		}

		os << " 0- Exit" << std::endl;
		os << "> ";
		
		return os;
	}

	unsigned int Menu::run() {
		unsigned int userInput;

		displayMenu();
		userInput = correctInput(0,menuPointers);
		
		return userInput;
	}

	int Menu:: operator ~() {
		return run();
	}

	

	Menu& Menu::operator <<(const char* menuItemContent) {
		if (menuPointers < MAX_MENU_ITEMS) {
			MenuItem* menuItemCopy = new MenuItem(menuItemContent);
			items[menuPointers] = menuItemCopy;
			menuPointers++;
		}

		return *this;
	}


	Menu::operator unsigned int() {
		return menuPointers;
	}


	Menu::operator int() {
		return menuPointers;
	}

	const char* Menu::operator[](unsigned int index)const {
		char* result;

		if (index > menuPointers) {
			result = items[0]->m_menuContent;
		} else {
			result = items[index]->m_menuContent;
		}

		return result;
	}


	Menu::operator bool() {
		bool result = false;

		if (menuPointers > 0) {
			result = true;
		}

		return result;
	}

	std::ostream& operator <<(std::ostream& os, Menu& menu) {
		return menu.displayTitle(os);
	}

}