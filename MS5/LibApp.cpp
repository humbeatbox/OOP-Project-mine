#include <iostream>
#include <fstream>
#include "LibApp.h"


using namespace std;
using namespace seneca;

namespace seneca {
//    Utils ut;

    bool LibApp::confirm(const char *message) {
        Menu menu(message);
        menu << "Yes";
        return (menu.run() == 1);
    }

    void LibApp::load() {
        cout << "Loading Data" << endl;
        //MS51
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
                //TODO:check this part
                inFile >> *m_ppa[m_nolp];
                m_llrn = m_ppa[m_nolp]->getRef();
                m_nolp++;
            }
        }
        //MS51
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

    int LibApp::search() {
        cout << "Searching for publication" << endl;
        //TODO:search part need implement
        //TODO:
        /*Add needed arguments so the search function can be called in three different modes:

        Search all
        Search Checkout Items Search only those publications which are on loan by library members
        Search Available Items Search only those publications which are not on loan
        Search will use an instance of PublicationSelector class to collect the search matches and user selection. The prompt of the PublicSelector should be: "Select one of the following found matches:" The page size for the selector menu should be 15 (the default value)

        First, get the type of publication to search for from the user. (user the type selection Menu of the class)

        Then print "Publication Title: " and get the title to search the PPA for. (up to 256 characters)

        Go through all the publications in the PPA and based on the method of search (all the items, on loan items or available ones) check each element and if the publication (pointed by the PPA element) is not deleted and type matches the selection of the user and the title contains the title the user entered, insert it into the PublicationSelector object.

                If matches are found, sort the result, get the user's selection and return the library reference number. If not print "No matches found!"

        If the user aborts at any stage print "Aborted!"*/
//        char insertTilte[257]{};
//        PublicationSelector selector("Select one of the following found matches:");
//        unsigned int pubType = m_pub_type.run();
//        char typeChar = ut.getType(pubType);
//        if (typeChar == 'X') {
//            cout << "Aborted!" << endl;
////            return -2;
//            //TODO:check idea
//        }else{
//            cout << "Publication Title: " << endl;
//            cin.getline(insertTilte,256);
//            insertTilte[256] = '\0';
//
//            for (int i = 0; i < m_nolp; i++) {
//                if(){}
//            }
//
//        }

        return 0;
    }
    /*  Calls the search() method.
    prints "Returning publication"<NEWLINE>
    prints "Publication returned"<NEWLINE>
    sets m_changed to true;
    */
    void LibApp::returnPub() {
        search();
        cout << "Returning publication" << endl;
        cout << "Publication returned" << endl;
        m_changed = true;
    }


    void LibApp::newPublication() {
//        cout << "Adding new publication to the library" << endl;
//        if(confirm("Add this publication to library?")){
//            m_changed = true;
//            cout << "Publication added" <<endl;
//        };
        //MS5
        if(m_nolp == SENECA_LIBRARY_CAPACITY){
            cout << "Library is at its maximum capacity!" << endl;
            return;
        }

        cout << "Adding new publication to the library" << endl;
//        char type = ut.getType();
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
            //cin.ignore(12000,'\n');
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
//        cout << "Failed to add publication!" << endl;
        //TODO: check logic



        //MS5
    }

    void LibApp::removePublication() {
        cout << "Removing publication from library" << endl;
        search();
        if(confirm("Remove this publication from the library?")){
            m_changed = true;
            cout << "Publication removed" <<endl;
        }
    }

    void LibApp::checkOutPub() {
        cout << "Checkout publication from the library" << endl;
        search();
        if(confirm("Check out publication?")){
            m_changed = true;
            cout << "Publication checked out" <<endl;
        }
    }

    LibApp::LibApp() {
        m_changed = {};
        //TODO:check the init of m_mainMenu and m_exitMenu
        m_mainMenu  //<< "Seneca Libray Application"
                    << "Add New Publication"
                    << "Remove Publication"
                    << "Checkout publication from library"
                    << "Return publication to library";

        m_exitMenu //<< "Changes have been made to the data, what would you like to do?"
                   << "Save changes and exit"
                   << "Cancel and go back to the main menu";
        //MS51
        m_pub_type << "Book" << "Publication";
        //MS51
        load();
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

//    LibApp::LibApp(const char *&filename) :LibApp(){
    LibApp::LibApp(const char *&filename) {
        //MS51
        m_changed = {};
        m_mainMenu  //<< "Seneca Libray Application"
                << "Add New Publication"
                << "Remove Publication"
                << "Checkout publication from library"
                << "Return publication to library";

        m_exitMenu //<< "Changes have been made to the data, what would you like to do?"
                << "Save changes and exit"
                << "Cancel and go back to the main menu";

        m_pub_type << "Book" << "Publication";
        strcpy(m_filename,filename);
        load();
        //MS51
    }

    Publication* LibApp::getPub(int libRef) {
        for (int i = 0; i < m_nolp; ++i) {
            if (m_ppa[i]->getRef() == libRef) {
                return m_ppa[i];
            }
        }
        return nullptr;
    }

    LibApp::~LibApp() {
        for (int i = 0; i < m_nolp; ++i) {
            delete m_ppa[i];
        }
    }

}
