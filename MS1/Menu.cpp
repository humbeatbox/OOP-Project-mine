//Name:Hsiao-Kang Chang
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-07-04 Creat this file

#include "Menu.h"
#include "Utils.h"
using namespace seneca;
using namespace std;
namespace seneca{
    Utils ut;
    MenuItem::MenuItem() {
        m_itemName = {};
    }
    //TODO: check the const is necessary or not
    MenuItem::MenuItem(const char *str) {
        if (str != nullptr && str[0] != '\0') {
            m_itemName = new char[strlen(str) + 1];
            strcpy(m_itemName,str);
        }
    }

    MenuItem::~MenuItem() {
        delete[] m_itemName;
    }

    MenuItem::operator bool() const {
        return m_itemName != nullptr && m_itemName[0] != '\0';
    }
    //return the address of m_itemName
    MenuItem::operator const char*()const{
        return m_itemName;
    }

    void MenuItem::display() const {
        if(m_itemName != nullptr && m_itemName[0] != '\0'){
            cout << m_itemName;
        }
    }

    Menu::Menu() {
        //no need just in case
        m_menuTitle = nullptr;
        noOfItems = 0;
    }
    Menu::Menu(char* str){
        m_menuTitle = new char[strlen(str)+1];
        strcpy(m_menuTitle,str);
        //no need just in case
        noOfItems = 0;
    }

    Menu::~Menu() {
        for (size_t i = 0; i < noOfItems; ++i) {
            if (m_menuItem[i] != nullptr)
                delete m_menuItem[i];
                m_menuItem[i] = nullptr;
        }
        delete[] m_menuTitle;
        m_menuTitle = nullptr;
    }

    void Menu::display()const{
        if(m_menuTitle != nullptr && m_menuTitle[0] != '\0'){
            cout << m_menuTitle << ":" << endl;
        }
        for (size_t i = 0; i <noOfItems ; ++i) {
            cout.width(2);
            cout.fill(' ');
            cout.setf(ios::right);
            cout << i+1;
            cout << "- " << m_menuItem[i]->m_itemName <<endl;
            cout.unsetf(ios::right);
        }
        cout << " 0- Exit" << endl << "> ";
    }

    unsigned int Menu::run() const {
        unsigned int ret{};
        ret = (unsigned int)ut.getInt(0,noOfItems);
        return ret;
    }

    unsigned int Menu::operator~() const {
        return run();
    }
    Menu& Menu::operator<<(const char* menuItemContent){
        if (noOfItems < MAX_MENU_ITEMS && noOfItems >= 0) {
            m_menuItem[noOfItems] = new MenuItem(menuItemContent);
            noOfItems++;
        }
        return *this;
    }
    Menu::operator int()const{
        return (int)noOfItems;
    }
    Menu::operator unsigned int() const {
        return (unsigned int)noOfItems;
    }

    Menu::operator bool() const {
        return noOfItems > 0;
    }

    const char *Menu::operator[](unsigned int index) const {
        return (const char*) *m_menuItem[index % MAX_MENU_ITEMS];
    }

    std::ostream& operator<<( std::ostream& ostr, const Menu& menu){
        //print the title of the Menu using cout.
        //cout << menu.m_menuTitle;
        return ostr << menu.m_menuTitle ;
        //TODO:fix the but it should be ok to cout the m_title
    }


}


