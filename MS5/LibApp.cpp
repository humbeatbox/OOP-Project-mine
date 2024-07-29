#include <iostream>
#include <fstream>
#include "LibApp.h"
#define SEARCH_ALL 1
#define SEARCH_CHECKOUT 2
#define SEARCH_AVAILABLE 3

using namespace std;
using namespace seneca;

namespace seneca {
    bool LibApp::confirm(const char *message) {
        Menu menu(message);
        menu << "Yes";
        return (menu.run() == 1);
    }

    void LibApp::load() {
        cout << "Loading Data" << endl;
        ifstream inFile(m_filename);
        char pub_type{};
        while (inFile){
            inFile >> pub_type;
            inFile.ignore();
            if(inFile){
                if (pub_type == 'P') {
                    m_ppa[m_nolp] = new Publication;
                }else if (pub_type == 'B') {
                    m_ppa[m_nolp] = new Book;
                }

                inFile >> *m_ppa[m_nolp];
                m_llrn = m_ppa[m_nolp]->getRef();
                m_nolp++;
            }
        }
    }

    void LibApp::save() {
        cout << "Saving Data" << endl;
        ofstream inFile(m_filename);
        for (int i = 0; i < m_nolp; ++i) {
            if (m_ppa[i]->getRef() != 0) {
                inFile << *m_ppa[i] << std::endl;
            }
        }
    }

    int LibApp::search(int searchOption) {
        char searchTitle[257]{};
        int reference = 0;
        char getTypeFromFile{};
        ifstream inFile(m_filename);
        cout << "Searching for publication" << endl;
        PublicationSelector pubSelect("Select one of the following found matches:");
        unsigned int pubType = m_pub_type.run();
        char typeChar = ut.getType(pubType);
        if (typeChar == 'X') {
            cout << "Aborted!" << endl;
//            return -2;
            reference = -1;//search fail
            //TODO:check idea
        }else {
            cout << "Publication Title: " << endl;
            cin.getline(searchTitle, 256);
            searchTitle[256] = '\0';
//            for (int i = 0;  inFile; ++i) {
            int i = 0;
                while(inFile){

                if (typeChar == 'P')
                    m_ppa[i] = new Publication;
                else if (typeChar == 'B')
                    m_ppa[i] = new Book;

                inFile >> getTypeFromFile;
                inFile.ignore();
                //get type from file

                if (m_ppa[i]) {
                    inFile >> *m_ppa[i];
                    switch(searchOption){
                        case SEARCH_ALL:
                            if (m_ppa[i]->type() == getTypeFromFile && *m_ppa[i] == searchTitle )
                                pubSelect << m_ppa[i++];
                            break;
                        case SEARCH_CHECKOUT:
                            if (*m_ppa[i] == searchTitle && m_ppa[i]->onLoan())
                                pubSelect << m_ppa[i++];
                            break;
                        case SEARCH_AVAILABLE:
                            if (*m_ppa[i] == searchTitle && !m_ppa[i]->onLoan())
                                pubSelect << m_ppa[i++];
                            break;
                        default:
                            break;
                    }

                }
/*                inFile >> getTypeFromFile;
                inFile.ignore();
                if (inFile) {
                    if (getTypeFromFile == 'P')
                        m_ppa[i] = new Publication;
                    else if (getTypeFromFile == 'B')
                        m_ppa[i] = new Book;
                    if (m_ppa[i]) {
                        inFile >> *m_ppa[i];
                        // find publications with Harry or MoneySence in the title
                        if (*m_ppa[i] == searchTitle)
                            pubSelect << m_ppa[i]; // insert into PublicationSelector if there is match
                    }
                }*/
            }

            if(pubSelect){
                pubSelect.sort();
                reference  = pubSelect.run();
                if (reference>0) {
                    return reference;
                }
                else {
                    cout << "Aborted by user!" << endl;
                }
            }
        }

//        }

        return 0;
    }
    /*  Calls the search() method.
    prints "Returning publication"<NEWLINE>
    prints "Publication returned"<NEWLINE>
    sets m_changed to true;
    */
    void LibApp::returnPub() {
        search(SEARCH_CHECKOUT);
        cout << "Returning publication" << endl;
        cout << "Publication returned" << endl;
        m_changed = true;
    }


    void LibApp::newPublication() {
        //MS5
        if(m_nolp == SENECA_LIBRARY_CAPACITY){
            cout << "Library is at its maximum capacity!" << endl;
            return;
        }
        cout << "Adding new publication to the library" << endl;
        unsigned int pubType = m_pub_type.run();
        char typeChar = ut.getType(pubType);
        Publication* pub = nullptr;
        if (typeChar == 'B') {
            pub = new Book();
            pub->read(cin);
        } else if (typeChar == 'P') {
            pub = new Publication();
            pub->read(cin);
        }else if (typeChar == 'X') {
            cout << "Aborted!" << endl;
            return;
        }

        if(cin.fail()){//get incorrect type
            cout << "Aborted!" << endl;
            cin.ignore(12000,'\n');
            delete[] pub;
            return;
        }
        {//cin good get correct type
            if(confirm("Add this publication to the library?")){//check add or not
                if (pub != nullptr){//pub is valid
                    m_llrn++;
                    pub->setRef(m_llrn);
                    m_ppa[m_nolp++] = pub;
                    m_changed = true;
                    cout << "Publication added" << endl;
                }else {
                    cout << "Failed to add publication!" << endl;
                    delete[] pub;
                }
            }else{//don't want to add
                cout << "Aborted!" << endl;
                delete[] pub;
                return;
            }
        }
        //MS5
    }

    void LibApp::removePublication() {
        cout << "Removing publication from library" << endl;
        search(SEARCH_ALL);
        if(confirm("Remove this publication from the library?")){
            m_changed = true;
            cout << "Publication removed" <<endl;
        }
    }

    void LibApp::checkOutPub() {
        cout << "Checkout publication from the library" << endl;
        search(SEARCH_AVAILABLE);
        if(confirm("Check out publication?")){
            m_changed = true;
            cout << "Publication checked out" <<endl;
        }
    }



    void LibApp::run() {
        bool done{};
        while (!done) {
            switch (m_mainMenu.run()) {
                case 1:
                    newPublication();
                    cout << endl;
                    break;
                case 2:
                    removePublication();
                    cout << endl;
                    break;
                case 3:
                    checkOutPub();
                    cout << endl;
                    break;
                case 4:
                    returnPub();
                    cout << endl;
                    break;
                case 0:
                    if (m_changed) {//change
                        switch (m_exitMenu.run()) {
                            case 0:
                                if (confirm("This will discard all the changes are you sure?")) {//1
                                    done = true;
                                    break;
                                }
                            case 1:
                                save();
                                done = true;
                                break;
                            case 2:
//                                if(confirm("This will discard all the changes are you sure?")){
//                                    done = true;
                                break;
                        }
                    } else {//no change but done
                        done = true;
                    }
                    cout << endl;
                    break;

            }

        }
        cout << "-------------------------------------------\n"
                "Thanks for using Seneca Library Application" << endl;
    }

    LibApp::LibApp() {
        m_changed = {};
        m_mainMenu
                << "Add New Publication"
                << "Remove Publication"
                << "Checkout publication from library"
                << "Return publication to library";
        m_exitMenu
                << "Save changes and exit"
                << "Cancel and go back to the main menu";
        m_pub_type << "Book" << "Publication";
        load();
    }

    LibApp::LibApp(const char *&filename) {
        m_changed = {};
        m_mainMenu
                << "Add New Publication"
                << "Remove Publication"
                << "Checkout publication from library"
                << "Return publication to library";
        m_exitMenu
                << "Save changes and exit"
                << "Cancel and go back to the main menu";
        m_pub_type << "Book" << "Publication";
        strcpy(m_filename,filename);
        load();
    }

    LibApp::~LibApp() {
        for (int i = 0; i < m_nolp; ++i) {
            delete m_ppa[i];
            m_ppa[i] = nullptr;
        }
    }

    Publication* LibApp::getPub(int libRef) {
        for (int i = 0; i < m_nolp; ++i) {
            if (m_ppa[i]->getRef() == libRef) {
                return m_ppa[i];
            }
        }
        return nullptr;
    }


}
