//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// Name : Thiago Flores
// Student ID : 150237220
// OOP244NAA

#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Menu.h"
#include "Lib.h"
#include "Publication.h"

namespace sdds {
   class LibApp {
	   char m_fileName[SDDS_MAX_ARRAY_LEN + 1];
	   //flag to keep track of changes intially set to false
	   bool m_changed;
	   //main menu of the application & menu items
	   Menu m_mainMenu;
	   //exit menu
	   Menu m_exitMenu;
	   Publication* m_PPA[SDDS_LIBRARY_CAPACITY];
	   int m_NOLP;
	   int m_LLRN;
	   Menu m_publicationType;


	   // different user choices of the menu will result in different terminal outputs
	   bool confirm(const char* message);
	   void load();
	   void save();
	   int search(int searchType);
	   void returnPub();

	   // different user choices that result in the menu actually being changed
	   void newPublication();
	   void removePublication();
	   void checkOutPub();

   public:
	   // LibApp constructor sets both the menus and the boolean to false
	   LibApp(const char* fileName = nullptr);
	   ~LibApp();

	   // loops and runs the program until the user decides to exit
	   void run();
	   //returns the address of a Publication object in the PPA that has the library reference number
	   Publication* getPub(int libRef);
   };
}
#endif // !SDDS_LIBAPP_H



