// File	Streamable.h
// Version 1.0
// Author	Hsiao-Kang Chang
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Hsiao-Kang Chang     07/08              init
/////////////////////////////////////////////////////////////////

#ifndef MS3_STREAMABLE_H
#define MS3_STREAMABLE_H
#include <iostream>

//using namespace std;
namespace seneca{
    class Streamable{
    public:
        virtual std::ostream& write(std::ostream&) const = 0;
        virtual std::istream& read(std::istream&) = 0;
        virtual bool conIO(std::ios& io)const = 0;
        virtual operator bool()const = 0;
        virtual ~Streamable() = 0;

        Streamable& operator<<(const Streamable&);
        Streamable& operator>>(Streamable&);
    };
}
#endif //MS3_STREAMABLE_H
