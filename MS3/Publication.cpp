//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// Name : Thiago Flores
// Student ID : 150237220
// OOP244NAA

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <cstring>
#include "Publication.h"

namespace sdds {
	Publication::Publication() {
		setDefault();
	}

	void Publication::setDefault() {
		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
		resetDate();
	}
	
	Publication::~Publication() {
		delete[] m_title;
	}

	Publication& Publication::operator=(const Publication& publication) {
		// we verify if we are not copying the same object
		if (this != &publication) {
			// we set the values of the object being copied
			set(publication.m_membership);
			setRef(publication.m_libRef);
			strcpy(m_shelfId, publication.m_shelfId);
			date = publication.date;

			// we delete the title if the object to be copied has data inside
			if (m_title) {
				delete[] m_title;
				m_title = nullptr;
			}
			
			// we only copy the title if its not a null pointer
			if (publication.m_title != nullptr) {
				m_title = new char[strlen(publication.m_title) + 1];
				strcpy(m_title, publication.m_title);
			}
			else {
				m_title = nullptr;
			}
		}

		return *this;
	}

	Publication::Publication(const Publication& publication) {
		*this = publication;
	}

	void Publication::set(int member_id) {
		// we validate that the number is within the correct range
		if (member_id < 0 || member_id > 99999) {
			m_membership = 0;
		}
		else {
			m_membership = member_id;
		}
	}

	void Publication::setRef(int value) {
		m_libRef = value;
	}

	void Publication::resetDate() {
		date = Date();
	}

	char Publication::type()const {
		return 'P';
	}

	bool Publication::onLoan()const {
		return m_membership != 0;
	}

	Date Publication::checkoutDate()const {
		return date;
	}

	bool Publication::operator==(const char* title)const {
		return strstr(m_title, title);
	}

	Publication::operator const char* ()const {
		return m_title;
	}

	int Publication::getRef()const {
		return m_libRef;
	}

	bool Publication::conIO(std::ios& io)const {
		return &io == &std::cin || &io == &std::cout;
	}
	
	std::ostream& Publication::write(std::ostream& os) const {
		if (conIO(os)) {
			os << "| " << m_shelfId << " | ";
			os << std::setw(30) << std::left << std::setfill('.') << m_title << " | ";
			
			if (m_membership != 0) {
				os << m_membership;
			}
			else {
				os << " N/A ";
			}

			os << " | " << date << " |";
		}
		else {
			os << type() << "\t" << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t";
			if (m_membership != 0) {
				os << m_membership;
			}
			else {
				os << " N/A ";
			}
			os << "\t" << date;
		}
		
		return os;
	}

	std::istream& Publication::read(std::istream& istr) {
		int l_libRef = -1;
		int l_membership = 0;
		char l_title[SDDS_TITLE_WIDTH + 1]{};
		char l_shelfId[SDDS_SHELF_ID_LEN + 1]{};
		Date l_date;

		if (m_title) {
			delete[] m_title;
			m_title = nullptr;
		}

		setDefault();

		if (conIO(istr)) {
			std::cout << "Shelf No: ";
			istr.getline(l_shelfId, SDDS_SHELF_ID_LEN + 1);

			if (strlen(l_shelfId) != SDDS_SHELF_ID_LEN) {
				istr.setstate(std::ios::failbit);
			}

			std::cout << "Title: ";
			istr.getline(l_title, SDDS_TITLE_WIDTH + 1);

			std::cout << "Date: ";
			istr >> l_date;
		}
		else {
			istr >> l_libRef;
			istr.ignore();
			istr.getline(l_shelfId,SDDS_SHELF_ID_LEN +1, '\t');
			istr.getline(l_title, SDDS_TITLE_WIDTH + 1, '\t');
			istr >> l_membership;
			istr.ignore();
			istr >> l_date;
		}

		if (!l_date) {
			istr.setstate(std::ios::failbit);
		}

		if (istr) {
			m_title = new char[strlen(l_title) + 1];
			strcpy(m_title, l_title);
			strcpy(m_shelfId, l_shelfId);
			m_membership = l_membership;
			date = l_date;
			m_libRef = l_libRef;
		}

		return istr;
	}

	Publication:: operator bool() const {
		return (m_title != nullptr && m_title[0] != '\0' && m_shelfId != nullptr && m_shelfId[0] != '\0');
	}
}