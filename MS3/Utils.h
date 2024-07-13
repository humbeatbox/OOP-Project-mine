/***********************************************************************
// OOP244 Utils Module
// File	Utils.h
// Version 
// Date	
// Author	
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//Hsiao-Kang Chang 07-05           add the getInt
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SENECA_UTILS_H__
#define SENECA_UTILS_H__
#include <iostream>
namespace seneca {
    class Utils {
    public:
        size_t getInt(size_t,size_t);
        void getCstr( char* str, size_t len );
    };
    extern Utils ut;
}
#endif // SENECA_UTILS_H__
