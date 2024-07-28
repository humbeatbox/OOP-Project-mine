#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H
#include "Menu.h"
#include "Publication.h"
#include "PublicationSelector.h"
#include "Book.h"
#include "Utils.h"
namespace seneca {
    class LibApp {
        bool m_changed{};
        Menu m_mainMenu={"Seneca Library Application"};
        Menu m_exitMenu={"Changes have been made to the data, what would you like to do?"};
        //MS5
        char m_filename[256]{};
        Publication* m_ppa[SENECA_LIBRARY_CAPACITY]{};//all the records of the publication data file
        int m_nolp{};//Number Of Loaded Publications
        int m_llrn{};//Last Library Reference Number
        Menu m_pub_type={"Choose the type of publication:"};
        Publication* getPub(int libRef);
        //MS5

        bool confirm(const char* message);

        void load();
        void save();
        int search();
        void returnPub();

        void newPublication();
        void removePublication();
        void checkOutPub();
    public:
        LibApp();
        LibApp(const char*&);
        void run();
    };
}
#endif // !SENECA_LIBAPP_H



