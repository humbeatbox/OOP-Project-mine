// File	Publication.h
// Version 1.0
// Author	Hsiao-Kang Chang
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Hsiao-Kang Chang     07/08              init
/////////////////////////////////////////////////////////////////


#include <iostream>
#include <ctime>
#include "Date.h"
#include "Lib.h"
#include "Streamable.h"

#ifndef MS3_PUBLICATION_H
#define MS3_PUBLICATION_H
#define MAX_TITLE_LEN 255
#define MAX_SHELF_LEN 4


//using namespace seneca;
namespace seneca{
    class Publication : public Streamable {
        char* m_title{};
        char m_shelfId[SENECA_SHELF_ID_LEN + 1]{};
        int m_membership{};
        int m_libRef = -1;
        Date m_date;
    public:
        Publication();
        ~Publication();
        virtual void set(int member_id);
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

        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& is);


    };
    std::istream& operator>>(std::istream&,Publication&);
    std::ostream& operator<<(std::ostream&,Publication&);
}
#endif //MS3_PUBLICATION_H
