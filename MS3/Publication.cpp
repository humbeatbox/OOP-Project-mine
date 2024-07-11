// File	Publication.cpp
// Version 1.0
// Author	Hsiao-Kang Chang
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Hsiao-Kang Chang     07/08              init
/////////////////////////////////////////////////////////////////
#include <cstring>
#include <iomanip>
#include "Publication.h"
#include "Utils.h"
#include "Date.h"
using namespace std;

using namespace seneca;

namespace seneca{
    Publication::Publication(){
        m_title = nullptr;//TODO:check how to limit less than 255 character
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
        m_date = Date();
    }
    Publication::~Publication(){
        if (m_title != nullptr) {
            delete[] m_title;
            m_title = nullptr;
        }
    }

    void Publication::set(int member_id) {
        if (member_id < 99999 && member_id >9999){
            m_membership = member_id;
        }
    }

    void Publication::setRef(int value) {
        m_libRef = value;
    }

    void Publication::resetDate() {
        m_date = Date();
    }

    char Publication::type() const {
        return 'P';
    }

    bool Publication::onLoan() const {
        return (m_membership != 0);
    }

    Date Publication::checkoutDate() const {
        return Date();
    }

    bool Publication::operator==(const char *title) const {
        return strstr(m_title, title) != nullptr;
    }

    Publication::operator const char *() const {
        return m_title;
    }

    int Publication::getRef() const {
        return m_libRef;
    }

    bool Publication::conIO(std::ios &io) const {
        return (&cin == &io) || (&cout == &io);
    }

    std::ostream& Publication::write(std::ostream& os) const{
        if (conIO(os)) {
            os << "| " << setw(SENECA_SHELF_ID_LEN)
               << m_shelfId
               << " | " << setw(SENECA_TITLE_WIDTH) <<setfill('.') << left
               << m_title
               << " | " << right;
            onLoan() ? os << m_membership : os << " N/A ";
            os << " | "
               << m_date
               << " |";
        } else {
            os << type() << '\t' << m_libRef << '\t' << m_shelfId << '\t' << m_title << '\t' << m_membership << '\t' << m_date;
        }
        return os;
    }
    std::istream& Publication::read(std::istream& is){
        //First, clear all the attributes by freeing the memory and setting everything to their default values.
        //constructor and de constructor instead
        delete[] m_title;
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
        m_date = Date();

        if (conIO(is)) {


        }

        return is;
    }
}