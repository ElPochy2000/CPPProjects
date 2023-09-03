//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// Name : Thiago Flores
// Student ID : 150237220
// OOP244NAA

#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>


namespace sdds {
	const unsigned int MAX_MENU_ITEMS = 20;

	
	
	class MenuItem {
		char* m_menuContent{};

		MenuItem();
		MenuItem(const char* menuContent);
		~MenuItem();

		// doesn't allow neither copies from constructor nor assigned to another menu Object
		MenuItem(const MenuItem& menuItem) = delete;
		void operator = (const MenuItem& menuItem) = delete;

		operator bool()const;
		operator char* ()const;

		std::ostream& display(std::ostream& os = std::cout)const;

		friend class Menu;
	};


	class Menu {
		MenuItem title{};
		MenuItem* items[MAX_MENU_ITEMS]{};
		unsigned int menuPointers = 0;

	public:
		Menu();
		Menu(const char* menuContent);
		~Menu();

		Menu(const Menu& menu) = delete;
		void operator = (const Menu& menu) = delete;

		std::ostream& displayTitle(std::ostream& os = std::cout);
		std::ostream& displayMenu(std::ostream& os = std::cout);

		unsigned int run();
		Menu& operator<<(const char* menuItemContent);

		const char* operator[](unsigned int index)const;
		int operator ~();
		operator unsigned int();
		operator int();
		operator bool();
	};

	std::ostream& operator <<(std::ostream& os, Menu& menu);
}
#endif