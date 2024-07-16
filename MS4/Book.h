//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-07-14 Creat this file
//Done on

//

#ifndef MS4_BOOK_H
#define MS4_BOOK_H
#include "Publication.h"
using namespace seneca;
namespace seneca{
    class Book : public Publication{
        char* m_authorName{};
    public:
        Book();
        //rule of three
        Book& operator=(const Book&);
        Book(const Book&);
        ~Book() override;

        char type()const override;
        std::ostream& write(std::ostream&) const override;
        std::istream& read(std::istream&) override;
        void set(int member_id) override;
        operator bool() const override;

        std::ostream &operator<<(std::ostream &os) override;
        std::istream &operator>>(std::istream &is) override;
    };
    std::ostream &operator<<(std::ostream &os, const Book& right);
    std::istream &operator>>(std::istream &is, Book& right);
}
#endif //MS4_BOOK_H
