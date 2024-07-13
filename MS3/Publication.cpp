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
//#include "Utils.h"
//#include "Date.h"
using namespace std;

using namespace seneca;

namespace seneca{
//    Publication::Publication(){
//        m_title = nullptr;//TODO:check how to limit less than 255 character
//        m_shelfId[0] = '\0';
//        m_membership = 0;
//        m_libRef = -1;
//        m_date = Date();
//    }
//, m_shelfId{ "" }
    Publication::Publication() : m_title(nullptr), m_membership(0), m_libRef(-1) {
        m_shelfId[0] = '\0';
        m_date = Date();
    }
    Publication::Publication(const Publication& P) {
        if (m_title != nullptr) {
            delete[] m_title;
            m_title = nullptr;
        }
        if (P.m_title != nullptr && P.m_title[0] != '\0') {
            m_title = new char[strlen(P.m_title) + 1];
            strcpy(m_title, P.m_title);
        }
        strcpy(m_shelfId, P.m_shelfId);
        m_membership = P.m_membership;
        m_libRef = P.m_libRef;
        m_date = P.m_date;
    }
//    Publication::Publication(const Publication& src) : Publication() {
//        *this = src;
//    }
    Publication& Publication::operator=(const Publication& P) {
        if (this != &P) {
            if (m_title != nullptr) {
                delete[] m_title;
                m_title = nullptr;
            }

            if (P.m_title != nullptr && P.m_title[0] != '\0') {
                m_title = new char[strlen(P.m_title) + 1];
                strcpy(m_title, P.m_title);
            }
            strcpy(m_shelfId, P.m_shelfId);
            m_membership = P.m_membership;
            m_libRef = P.m_libRef;
            m_date = P.m_date;
        }
        return *this;
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
//        return Date();
        return m_date;
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
        if (!(*this) || !m_date)
        return os;
        if (conIO(os)) {
//            os << "| " << setw(SENECA_SHELF_ID_LEN)
//               << m_shelfId
//               << " | " << setw(SENECA_TITLE_WIDTH) <<setfill('.') << left
//               << m_title
//               << " | " << right;
//            onLoan() ? os << m_membership : os << " N/A ";
//            os << " | "
//               << m_date
//               << " |";
//              BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
            os << "| ";
            os.width(SENECA_SHELF_ID_LEN);
            os << m_shelfId;
            os << " | ";
            os.width(SENECA_TITLE_WIDTH);
            os.fill('.');
            os << left << m_title;
            os << " | ";
            m_membership >= 10000 && m_membership < 100000 ?
            os << m_membership : os << " N/A ";
            os << " | ";
            os << m_date;
            os << " |";
        } else {
            os << type() << '\t' << m_libRef << '\t' << m_shelfId << '\t' << m_title << '\t' << m_membership << '\t' << m_date;
        }
        return os;
    }
    std::istream& Publication::read(std::istream& istr){
        //First, clear all the attributes by freeing the memory and setting everything to their default values.
        //constructor and de constructor instead
        delete[] m_title;
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
        m_date = Date();


        //char *titleTmp = nullptr;
        string titleTmp = {};
        char shelfTmp[SENECA_SHELF_ID_LEN + 1]{};
        int membershipTmp = 0;
        int libRefTmp = -1;
        Date dateTmp;

        if (conIO(istr)) {
            cout << "Shelf No: ";
            istr >> shelfTmp;
            if(strlen(shelfTmp) != SENECA_SHELF_ID_LEN){
                istr.setstate(std::ios::failbit);
            }else {
                istr.ignore();
            }
            cout << "Title: ";
            if(!istr.fail()){
                //istr.getline(titleTmp,1000,'\n');
                getline(cin,titleTmp);
            }

            //istr.ignore( 12000, '\n' );
            cout << "Date: ";
            if(!istr.fail()){
                dateTmp.read();//read date
                if(!dateTmp){
                    istr.setstate(std::ios::failbit);
                }
            }


        }else{
            istr >> libRefTmp;
            istr.ignore();//only skip tab
            istr.getline(shelfTmp,SENECA_SHELF_ID_LEN + 1 ,'\t');
//            istr.getline(titleTmp,1000,'\t');
            getline(cin,titleTmp);
            istr >> membershipTmp;
            istr.ignore();
            dateTmp.read();
            if(!dateTmp){
                istr.setstate(std::ios::failbit);
            }
        }
        //After the process of reading is done if istr is in a valid state:
        if (!istr.fail()){
            if(titleTmp[0] != '\0'){
                delete m_title;
                m_title = nullptr;
                m_title = new char[strlen(titleTmp.c_str()) + 1 ];
                strcpy(m_title,titleTmp.c_str());
            }
            if(shelfTmp[0] != '\0'){
                strcpy(m_shelfId,shelfTmp);
            }
            m_membership = membershipTmp;
            m_libRef = libRefTmp;
            m_date = dateTmp;
        }
        return istr;
    }

    Publication::operator bool() const {
        return m_title != nullptr && m_shelfId[0] != '\0';
    }

    ostream &Publication::operator<<(ostream &os) {
        return write(os);
    }

    istream &Publication::operator>>(istream &is) {
        return read(is);
    }


    ostream &operator<<(ostream &os, const Publication& right) {
        return right.write(os);
    }
    istream &operator>>(istream &is, Publication& right) {
        return right.read(is);
    }
}

