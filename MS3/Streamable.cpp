// File	Streamable.cpp
// Version 1.0
// Author	Hsiao-Kang Chang
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Hsiao-Kang Chang     07/08              init
/////////////////////////////////////////////////////////////////
#include "Streamable.h"
using namespace seneca;
using namespace std;

namespace seneca{

    Streamable& Streamable::operator<<(const Streamable &S) {
        return *this;
    }

    Streamable& Streamable::operator>>(Streamable &S) {
        return *this;
    }
}
