//Name:Hsiao-Kang Chang
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-07-14 Creat this file
//Done on

//
#include <cstring>
#include <iomanip>
#include "Book.h"

using namespace seneca;
using namespace std;
namespace seneca{

    Book::Book() : m_authorName{nullptr}{
    }

    Book &Book::operator=(const Book &B) {
        if(this != &B && B.m_authorName != nullptr){
            delete[] m_authorName;
            m_authorName = nullptr;
            m_authorName  = new char[strlen(B.m_authorName) + 1];
            strcpy(m_authorName,B.m_authorName);
            Publication::operator=(B);

        }else{
            delete[] m_authorName;
            m_authorName = nullptr;
        }
        return *this;
    }

    Book::Book(const Book &B)  : Publication(B), m_authorName(nullptr) {
        *this = B;
    }
    Book::~Book(){
        delete[] m_authorName;
        m_authorName = nullptr;
    }

    char Book::type() const {
        return 'B';
    }

    std::ostream &Book::write(std::ostream &os) const {
        if (!(*this) ||! m_authorName)
            return os;
        Publication::write(os);
        if(Publication::conIO(os)){
            os << ' '   ;

            if (m_authorName && m_authorName[0] != '\0'){
                if(strlen(m_authorName) > SENECA_AUTHOR_WIDTH){
                    os.write(m_authorName,SENECA_AUTHOR_WIDTH);
                } else {
                    os << setw(SENECA_AUTHOR_WIDTH) << left << setfill('.');
                    os << m_authorName;
                }
            }
            os << right << setfill(' ') << " |";
        }else{
            os << '\t' << m_authorName;
        }
        os << setfill(' ');
        return os;
    }

    std::istream &Book::read(istream &is) {
        char authorName[255]{};
        Publication::read(is);

        if(m_authorName != nullptr){
            delete[] m_authorName;
            m_authorName = nullptr;
        }

        if(Publication::conIO(is)){
            is.ignore(1,'\n');
            cout << "Author: ";
            is.getline(authorName, 256,'\n');
        }else{
            is.ignore(1,'\t');
            is.getline(authorName, 255,'\n');
        }

        if(!is.fail()){
            m_authorName = new char[strlen(authorName) + 1];
            strcpy(m_authorName,authorName);
        }
        return is;
    }

    void Book::set(int member_id) {
        Publication::set(member_id);
        Publication::resetDate();
    }

    Book::operator bool() const {
        return (m_authorName != nullptr && m_authorName[0] != '\0' && Publication::operator bool());
    }

    ostream &Book::operator<<(ostream &os) {
        return write(os);
    }
    istream &Book::operator>>(istream &is) {
        return read(is);
    }

    ostream &operator<<(ostream &os, const Book& right) {
        return right.write(os);
    }
    istream &operator>>(istream &is, Book& right) {
        return right.read(is);
    }
}

/*

#include "Book.h"

using namespace std;

namespace seneca {
    Book::Book() {
        m_authorName = nullptr;
    }

    Book::~Book() {
        if (m_authorName != nullptr) {
            delete[] m_authorName;
            m_authorName = nullptr;
        }
    }

    Book::Book(const Book &b) : Publication(b) {
        if (b.m_authorName != nullptr) {
            m_authorName = new char[strlen(b.m_authorName) + 1];
            strcpy(m_authorName, b.m_authorName);
        }
    }

    Book &Book::operator=(const Book &b) {
        if (this != &b && b.m_authorName != nullptr) {
            delete[] m_authorName;
            m_authorName = new char[strlen(b.m_authorName) + 1];
            strcpy(m_authorName, b.m_authorName);
            Publication::operator=(b);
        }
        return *this;
    }

    char Book::type() const {
        return 'B';
    }

    std::ostream &Book::write(std::ostream &os) const {
        if (!(*this))
            return os;
        Publication::write(os);
        string authorName(m_authorName);

        if (Publication::conIO(os)) {
            os << ' ';
            os.width(SENECA_AUTHOR_WIDTH);
            os.fill(' ');
            if (authorName.length() > SENECA_AUTHOR_WIDTH)
                os << left << authorName.substr(0, SENECA_AUTHOR_WIDTH);
            else
                os << left << authorName;
            os << " |";
        } else {
            os << '\t' << authorName;
        }

        return os;
    }

    std::istream &Book::read(std::istream &is) {
        Publication::read(is);
        char buf[256];

        if (m_authorName != nullptr) {
            delete[] m_authorName;
            m_authorName = nullptr;
        }

        if (Publication::conIO(is)) {
            is.ignore(1000, '\n');
            cout << "Author: ";
            is.get(buf, 256, '\n');
        } else {
            is.ignore(1000, '\t');
            is.get(buf, 256, '\n');
        }

        if (!is.fail() && buf[0] != '\0') {
            m_authorName = new char[strlen(buf) + 1];
            strcpy(m_authorName, buf);
        }

        return is;
    }

    void Book::set(int member_id) {
        Publication::set(member_id);
        Publication::resetDate();
    }

    Book::operator bool() const {
        return m_authorName != nullptr && m_authorName[0] != '\0' && Publication::operator bool();
    }

    ostream &Book::operator<<(ostream &os) {
        return write(os);
    }
    istream &Book::operator>>(istream &is) {
        return read(is);
    }

    ostream &operator<<(ostream &os, const Book& right) {
        return right.write(os);
    }
    istream &operator>>(istream &is, Book& right) {
        return right.read(is);
    }
}*/
