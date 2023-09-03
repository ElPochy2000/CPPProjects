//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// Name : Thiago Flores
// Student ID : 150237220
// OOP244NAA

#ifndef BOOK_H
#define BOOK_H
#include "Publication.h"

namespace sdds {
	class Book : public Publication {
		// Holds the name of the books author
		char* m_authorName{};

	public:
		Book();
		Book(const Book& book);
		Book& operator=(const Book& book);
		virtual ~Book();

		virtual char type()const;
		virtual void set(int member_id);

		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& os);

		operator bool() const;
	};


}

#endif // !BOOK_H
