//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// Name : Thiago Flores
// Student ID : 150237220
// OOP244NAA

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Book.h"
#include <iomanip>


using namespace std;

namespace sdds {
	Book::Book() : Publication (){
		m_authorName = nullptr;
	}

	Book::Book(const Book& book){
		*this = book;
	}

	Book& Book::operator=(const Book& book) {
		if (this != &book) {
			Publication::operator=(book);

			if (m_authorName) {
				delete[] m_authorName;
				m_authorName = nullptr;
			}
			if (book.m_authorName) {
				m_authorName = new char[strlen(book.m_authorName) + 1];
				strcpy(m_authorName, book.m_authorName);
			}
		}

		return *this;
	}

	Book::~Book() {
		delete[] m_authorName;
		m_authorName = nullptr;
	}

	char Book::type()const {
		return 'B';
	}

	std::ostream& Book::write(std::ostream& os) const {
		Publication::write(os);

		if (conIO(os)) {
			//We must copy the m_author this way to match with the expected output
			char author[SDDS_AUTHOR_WIDTH + 1]{};
			strncpy(author, m_authorName, SDDS_AUTHOR_WIDTH);
			os << " " << setw(SDDS_AUTHOR_WIDTH) << left << setfill(' ') << author << " |";
		}
		else {
			os << "\t" << m_authorName;
		}

		return os;
	}

	std::istream& Book::read(std::istream& is){
		char author[SDDS_MAX_ARRAY_LEN];

		Publication::read(is);

		if (m_authorName) {
			delete[] m_authorName;
			m_authorName = nullptr;
		}

		if (conIO(is)) {
			is.ignore();
			cout << "Author: ";
		}
		else {
			is.ignore(1000, '\t');
		}

		is.get(author, SDDS_MAX_ARRAY_LEN);

		if (is) {
			m_authorName = new char[strlen(author) + 1];
			strcpy(m_authorName, author);
		}

		return is;
	}

	void Book::set(int member_id) {
		Publication::set(member_id);
		Publication::resetDate();
	}

	Book::operator bool() const {
		return m_authorName && Publication::operator bool();
	}
}