// Final Project Milestone 1 
// Date Module
// File	Date.cpp
// Version 1.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"
namespace sdds {
   bool Date::validate() {
      errCode(NO_ERROR);
      if (m_year < MIN_YEAR || m_year > m_CUR_YEAR + 1) {
         errCode(YEAR_ERROR);
      }
      else if (m_mon < 1 || m_mon > 12) {
         errCode(MON_ERROR);
      }
      else if (m_day < 1 || m_day > mdays()) {
         errCode(DAY_ERROR);
      }
      return !bad();
   }
   int Date::mdays()const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
      mon--;
      return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
   }
   int Date::systemYear()const {
      time_t t = time(NULL);
      tm lt = *localtime(&t);
      return lt.tm_year + 1900;
   }
   void Date::setToToday() {
      time_t t = time(NULL);
      tm lt = *localtime(&t);
      m_day = lt.tm_mday;
      m_mon = lt.tm_mon + 1;
      m_year = lt.tm_year + 1900;
      errCode(NO_ERROR);
   }
   int Date::daysSince0001_1_1()const { // Rata Die day since 0001/01/01 
      int ty = m_year;
      int tm = m_mon;
      if (tm < 3) {
         ty--;
         tm += 12;
      }
      return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
   }
   Date::Date() :m_CUR_YEAR(systemYear()) {
      setToToday();
   }
   Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear()) {
      m_year = year;
      m_mon = mon;
      m_day = day;
      validate();
   }
   const char* Date::dateStatus()const {
      return DATE_ERROR[errCode()];
   }
   int Date::currentYear()const {
      return m_CUR_YEAR;
   }
   void Date::errCode(int readErrorCode) {
      m_ErrorCode = readErrorCode;
   }
   int Date::errCode()const {
      return m_ErrorCode;
   }
   bool Date::bad()const {
      return m_ErrorCode != 0;
   }
  
   ostream& operator<<(ostream& os, const Date& RO) {
      return RO.write(os);
   }
   istream& operator>>(istream& is, Date& RO) {
      return RO.read(is);
   }

   std::istream& Date::read(std::istream& is) {

       // We clear any possible previous error code
       errCode(NO_ERROR);

       // this will input the cin received by the user until the int is finished and a new data type is received
       // modifying the m_year part of the object
       is >> m_year;
       //ignores the character after the int is read
       is.ignore();
       is >> m_mon;
       is.ignore();
       is >> m_day;

       if (!is) {
           // clears istream
           is.clear();
           // clears buffer
           is.ignore(1000, '\n');
           // we set the error code
           errCode(CIN_FAILED);
       }
       else {
           validate();
       }

       return is;
   }

   std::ostream& Date::write(std::ostream& os)const {
       if (bad()) {
           os << dateStatus();
       }
       else {
           os << m_year;
           os << "/";
           os.width(2);
           os.fill('0');
           os.setf(ios::right);
           os << m_mon;
           os << "/";
           os.width(2);
           os.fill('0');
           os.setf(ios::right);
           os << m_day;
       }
       return os;
   }

   bool Date::operator ==(const Date& date)const {
       return daysSince0001_1_1() == date.daysSince0001_1_1();
   } 

   bool Date::operator !=(const Date& date)const {
       return daysSince0001_1_1() != date.daysSince0001_1_1();
   }

   bool Date::operator >=(const Date& date)const {
       return daysSince0001_1_1() >= date.daysSince0001_1_1();
   }

   bool Date::operator <=(const Date& date)const {
       return daysSince0001_1_1() <= date.daysSince0001_1_1();
   }

   bool Date::operator <(const Date& date)const {
       return daysSince0001_1_1() < date.daysSince0001_1_1();
   }

   bool Date::operator >(const Date& date)const {
       return daysSince0001_1_1() > date.daysSince0001_1_1();
   }

   int Date::operator - (const Date& date)const {
       /*int result;


       if (this->daysSince0001_1_1() >= date.daysSince0001_1_1()) {
            result = this->daysSince0001_1_1() - date.daysSince0001_1_1();
       }
       else {
           result = date.daysSince0001_1_1() - this->daysSince0001_1_1();
       }*/

       return this->daysSince0001_1_1() - date.daysSince0001_1_1();;
   }

   Date::operator bool()const {
       return !bad();
   }
}
