/**------------------------------------------
    Program 4: Contact Lists (Part 2)

    Course: CS 141, Spring 2023.
    System: Linux x86_64 and C++
    Author: Soham Kaje, starter code provided by Professors George Maratos and
    David Hayes
 ---------------------------------------------**/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Contact.h"
#include "ContactList.h"

// this function displays the original options that the user can do with regards to their contact list
void display_menu_options() {
  cout << "********************************************" << endl;
  cout << "Main Menu" << endl;
  cout << endl;
  cout << "Enter the letter for the desired menu option:" << endl;
  cout << "   C - Get count" << endl;
  cout << "   L - Load contacts from file" << endl;
  cout << "   S - Search contacts" << endl;
  cout << "   P - Print contacts" << endl;
  cout << "   X - Exit" << endl;
  cout << endl;
}

// this function outputs the amount of contacts in the user's list
void count(ContactList &list) {
  // calls getCount function from ContactList.cpp to output the number of contacts in the list
  cout << "There are " << list.getCount() << " contacts" << endl << endl;
}

// this function loads the contacts that the user wants to view
void load(ContactList &list) {
  string filename;
  cout << "Enter a filename" << endl;

  cin >> filename;

  // calls loadContactsFromFile function from ContactList.cpp to add the contacts to the list 
  string loaded = list.loadContactsFromFile(filename);
  cout << loaded << endl << endl;
}

// this function allows the user to edit or manipulate information in specific contacts or their contact list
void edit(ContactList &list, Contact &temp) {
  // output options for editing contact
  cout << "Enter an option for contact:" << endl;
  cout << "   A - Edit address" << endl;
  cout << "   B - Edit date of birth" << endl;
  cout << "   E - Edit email address" << endl;
  cout << "   N - Edit name" << endl;
  cout << "   P - Edit phone numbers" << endl;
  cout << "   R - Return to main menu" << endl;
  cout << "   D - Delete" << endl;

  char input;
  cin >> input;
  input = toupper(input);

  // edit email option
  if (input == 'E') {
    cout << endl;
    cout << "Current email:" << endl;
    cout << temp.getEmail() << endl << endl;
    cout << "Enter new email or C to cancel:" << endl;

    string input2;
    cin >> input2;

    // checks whether user wants to cancel editing email
    if (input2 == "C") {
      return;
    } 
    // updates email of contact in list
    else { 
      string name = temp.getName();
      vector<int> pos = list.findContactsByName(name);
      list.getContact(pos[0])->setEmail(input2);
      temp.setEmail(input2);
    }
    
    cout << endl;
    cout << "Email updated:" << endl;
    cout << temp.getEmail() << endl;
    return;
  } 
  //edit phone numbers option
  else if (input == 'P') {
    vector<string> phones = temp.getPhoneNumbers();
    // plural check
    if (phones.size() == 1) {
      cout << "Found " << phones.size() << " phone number" << endl;
    } else {
      cout << "Found " << phones.size() << " phone numbers" << endl;
    }

    // lists the phone numbers
    for (int i = 0; i < phones.size(); i++) {
      cout << i + 1 << ". " << phones.at(i) << endl;
    }

    cout << "Enter an option:" << endl;
    cout << "   A - Add a phone number" << endl;
    cout << "   R - Return to main menu" << endl;
    cout << "   or list number to delete" << endl;

    string input4;
    cin >> input4;
    char character2;
    int num2;

    // checks whether input is a number or letter
    for (int y = 0; y < input4.size(); y++) {
      if (isalpha(input4[y])) {
        character2 = toupper(input4[y]);
        break;
      } else if (isdigit(input4[y])) {
        if (y == input4.size() - 1) {
          num2 = stoi(input4);
        } else {
          continue;
        }
      }
    }

    // adds phone number to list
    if (character2 == 'A') {
      cout << "Enter the letter for the phone number type:" << endl;
      cout << "C(ell), W(ork) or H(ome)";

      char input6;
      cin >> input6;
      string type;

      // determines type of phone
      input6 = toupper(input6);
      if (input6 == 'C') {
        type = "Cell";
      } else if (input6 == 'W') {
        type = "Work";
      } else if (input6 == 'H') {
        type = "Home";
      }

      string phone;
      cout << "Enter the phone number:";
      cin >> phone;

      // updates contact in list with new phone number
      string name = temp.getName();
      vector<int> pos = list.findContactsByName(name);
      list.getContact(pos[0])->addPhone(input6, phone);
      cout << "success: added number " << phone << " " << type << endl << endl;
      return;
    } 
    // returns to main menu
    else if (character2 == 'R') {
      return;
    } 
    // deletes phone from selected contact in list
    else {
      cout << "Are you sure you want to delete phone: " << phones.at(num2 - 1)
           << "?" << endl;
      cout << "Enter 'Y' to confirm." << endl;

      string input5;
      cin >> input5;

      // deletes phone number from contact in list
      if (input5 == "Y") {
        string typenumber = phones.at(num2 - 1);
        string number;
        for (int x = 0; x < typenumber.size(); x++) {
          if (x >= 5) {
            number += typenumber.at(x);
          }
        }
        cout << "success: deleted phone " << number << endl;
        string name = temp.getName();
        vector<int> pos = list.findContactsByName(name);
        list.getContact(pos[0])->deletePhone(num2 - 1);
        return;
      }
    }
  } 
  // returns to main menu
  else if (input == 'R') {
    return;
  } 
  // delete contact option
  else if (input == 'D') {
    cout << "Are you sure you want to delete contact " << temp.getName() << "?"
         << endl;
    cout << "Enter 'Y' to confirm." << endl;
    string input3;
    cin >> input3;
    // deletes contact from list
    if (input3 == "Y" || input3 == "y") {
      string name = temp.getName();
      vector<int> pos = list.findContactsByName(name);
      list.deleteContact(pos[0]);
      cout << "success: deleted contact " << name << endl;
    }
  }
}

// function to search for keyword in contacts and check whether user wants to print, return, or check a specific contact
void search(ContactList &list) {
  cout << endl;
  cout << "Enter a search term" << endl;

  string term;
  cin >> term;
  cout << endl;

  // vector of indexes where specific contacts are in the list
  vector<int> positions = list.findContactsByName(term);
  
  // plural check
  if (positions.size() > 1) {
    cout << "Found " << positions.size() << " results" << endl;
  } else if (positions.size() == 1) {
    cout << "Found " << positions.size() << " result" << endl;
  }

  // declared vector of specific contacts, for loop to add them to the vector
  vector<Contact> found;
  for (int i = 0; i < positions.size(); i++) {
    cout << i + 1 << ". " << list.getContact(positions.at(i))->getName()
         << endl;
    found.push_back(*(list.getContact(positions.at(i))));
  }

  // display options
  cout << endl;
  cout << "Enter an option:" << endl;
  cout << "   P - Print contacts" << endl;
  cout << "   or a Contact number to view/edit" << endl;
  cout << "   R - Return to main menu" << endl;
  
  string input;
  cin >> input;
  cout << endl;
  char character;
  int num;

  // checks whether input is letter or number
  for (int y = 0; y < input.size(); y++) {
    if (isalpha(input[y])) {
      character = input[y];
      break;
    } else if (isdigit(input[y])) {
      if (y == input.size() - 1) {
        num = stoi(input);
      } else {
        continue;
      }
    }
  }

  // print all contacts that were searched
  if (toupper(character) == 'P') {
    for (int j = 0; j < positions.size(); j++) {
      cout << "--------------------" << endl << endl;
      cout << list.getContact(positions.at(j))->getAsString() << endl;
    }
    cout << endl;
  } 
  // returns to main menu
  else if (toupper(character) == 'R') {
    return;
  } 
  // displays contact chosen in the list and calls edit function to see whether user wants to edit any info in that contact
  else {
    cout << endl;
    Contact temp = found.at(num - 1);
    cout << temp.getAsString() << endl;
    edit(list, temp);
  }
}

int main() {
  char choice;
  ContactList list;
  do { // do while loop to run program until the user chooses the exit.
    display_menu_options();
    cin >> choice;
    switch (toupper(choice)) {
    case 'C': { // menu option Get Count
      count(list);
      break;
    }
    case 'L': { // menu option Load Contacts
      load(list);
      break;
    }
    case 'S': { // menu option Search/Edit
      search(list);
      break;
    }
    }
    cout << endl;
  } while ((toupper(choice) != 'X') && !cin.eof());

  return 0;
}
