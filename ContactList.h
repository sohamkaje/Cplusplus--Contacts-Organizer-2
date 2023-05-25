#ifndef CONTACTLIST_H
#define CONTACTLIST_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "Contact.h"

using namespace std;


class ContactList {

  public:
    string loadContactsFromFile (string filename);
    int getCount();
    string sortContacts();
    vector<int> findContactsByName(string searchTerm);
    void printContacts();
    void printContacts (vector<int> positions);
    string addContact (Contact c);
    string deleteContact (int idx);
    Contact* getContact(int idx);
    string tester();

  private:
    vector<Contact> contacts;

};


#endif
