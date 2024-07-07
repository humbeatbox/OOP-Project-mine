#include <iostream>
#include "LibApp.h"

using namespace std;
using namespace seneca;

namespace seneca {


    bool LibApp::confirm(const char *message) {
        Menu menu(message);
        menu << "yes";
        return (menu.run() == 1);
    }

    void LibApp::load() {
        cout << "Loading Data" << endl;
    }

    void LibApp::save() {
        cout << "Saving Data" << endl;

    }

    void LibApp::search() {
        cout << "Searching for publication" << endl;
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
        cout << "Adding new publication to library" << endl;
        if(confirm("Add this publication to library?")){
            m_changed = true;
            cout << "Publication added" <<endl;
        };
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
}
