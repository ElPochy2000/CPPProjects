//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// Name : Thiago Flores
// Student ID : 150237220
// OOP244NAA

#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <iostream>
#include "Streamable.h"
#include "Date.h"
#include "Lib.h"

namespace sdds {
	class Publication : public Streamable{
		char* m_title;
		char m_shelfId[SDDS_SHELF_ID_LEN + 1];
		int m_membership;
		int m_libRef;
		Date date;

	public:
		// Constructor sets values to default
		Publication();
		// Destructor
		virtual ~Publication();

		// Copy constructors
		Publication(const Publication& publication);
		Publication& operator=(const Publication& publication);

		void set(int member_id);
		// Sets the membership attribute to either zero or a five-digit integer.
		void setRef(int value);
		// Sets the **libRef** attribute value
		void resetDate();
		// Sets the date to the current date of the system.

		virtual char type()const;
		//Returns the character 'P' to identify this object as a "Publication object"
		bool onLoan()const;
		//Returns true is the publication is checkout (membership is non-zero)
		Date checkoutDate()const;
		//Returns the date attribute
		bool operator==(const char* title)const;
		//Returns true if the argument title appears anywhere in the title of the 
		//publication. Otherwise, it returns false; (use strstr() function in <cstring>)
		operator const char* ()const;
		//Returns the title attribute
		int getRef()const;
		//Returns the libRef attirbute. 

		bool conIO(std::ios& io)const;
		//Returns true if the address of the io object is the same as the address of either the cin object or the cout object.
		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& istr);

		void setDefault();
		// sets values to default

		operator bool() const;
		// Returns true if neither of the title or shelfId attributes is null or empty. Otherwise, it will return false.
	};

}

#endif // !PUBLICATION_H
