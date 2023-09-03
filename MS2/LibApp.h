//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// Name : Thiago Flores
// Student ID : 150237220
// OOP244NAA

#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Menu.h"

namespace sdds {
   class LibApp {
	   //flag to keep track of changes intially set to false
	   bool m_changed;
	   //main menu of the application & menu items
	   Menu m_mainMenu;
	   //exit menu
	   Menu m_exitMenu;

	   // different user choices of the menu will result in different terminal outputs
	   bool confirm(const char* message);
	   void load();
	   void save();
	   void search();
	   void returnPub();

	   // different user choices that result in the menu actually being changed
	   void newPublication();
	   void removePublication();
	   void checkOutPub();

   public:
	   // LibApp constructor sets both the menus and the boolean to false
	   LibApp();
	   // loops and runs the program until the user decides to exit
	   void run();
   };
}
#endif // !SDDS_LIBAPP_H



