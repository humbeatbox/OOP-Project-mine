#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H
#include "Menu.h"
namespace seneca {
    class LibApp {
        bool m_changed{};
        Menu m_mainMenu={"Seneca Library Application"};
        Menu m_exitMenu={"Changes have been made to the data, what would you like to do?"};
        bool confirm(const char* message);

        void load();  // prints: "Loading Data"<NEWLINE>
        void save();  // prints: "Saving Data"<NEWLINE>
        void search();  // prints: "Searching for publication"<NEWLINE>
        void returnPub();

        void newPublication();
        void removePublication();
        void checkOutPub();
    public:
        LibApp();
        void run();
    };
}
#endif // !SENECA_LIBAPP_H



