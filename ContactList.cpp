#include "ContactList.h"
// #include "Contact.h"

using namespace std;

int ContactList::getCount() { return contacts.size(); };

string ContactList::addContact(Contact c) {

  string result = "";

  contacts.push_back(c);

  result = "success: contact " + c.getName() + " added";

  return result;
}

string ContactList::sortContacts() {

  string result = "success";
  sort(contacts.begin(), contacts.end());
  return result;
}

vector<int> ContactList::findContactsByName(string searchTerm) {

  vector<int> result;
  string nameUpper;
  transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(),
            ::toupper);

  for (int i = 0; i < contacts.size(); i++) {
    nameUpper = contacts.at(i).getName();
    transform(nameUpper.begin(), nameUpper.end(), nameUpper.begin(), ::toupper);

    if (nameUpper.find(searchTerm) != string::npos) {
      result.push_back(i);
    }
  }

  return result;
}

void ContactList::printContacts() {
  vector<int> positions;

  for (int i = 0; i < contacts.size(); i++) {
    positions.push_back(i);
  }

  printContacts(positions);
}

void ContactList::printContacts(vector<int> positions) {

  string separator = "--------------------";

  for (int idx : positions) {
    cout << separator << "\n\n" << contacts.at(idx).getAsString() << "\n";
  }
}

string ContactList::deleteContact(int idx) {
  string result, fullName;

  if (idx < contacts.size()) {
    fullName = contacts.at(idx).getName();
    contacts.erase(contacts.begin() + idx);
    result = "success: deleted contact " + fullName;
  } else {
    result = "failure: unable to contact " + to_string(idx);
  }

  return result;
}

string ContactList::loadContactsFromFile(string filename) {

  ifstream inFS;
  string result;
  int numContactsAdded = 0;

  char contactType;
  string firstName, lastName, streetName, city, state, email, dateOfBirth,
      element;
  int streetNumber, postalCode;

  inFS.open(filename);
  if (!inFS.is_open()) {
    result = "failure: " + filename + " not found";
  } else {

    getline(inFS, element); // skip first line

    // read in enough to create a Contact
    while (getline(inFS, element, ',')) {
      contactType = toupper(element.at(0));
      getline(inFS, firstName, ',');
      getline(inFS, lastName, ',');
      Contact c(contactType, firstName, lastName);

      // read in and set address values
      getline(inFS, element, ',');
      streetNumber = stoi(element);
      getline(inFS, streetName, ',');
      getline(inFS, city, ',');
      getline(inFS, state, ',');
      getline(inFS, element, ',');
      postalCode = stoi(element);

      c.setAddress(streetNumber, streetName, city, state, postalCode);

      getline(inFS, email, ',');
      c.setEmail(email);

      getline(inFS, dateOfBirth, ',');
      c.setDateOfBirth(dateOfBirth);

      getline(inFS, element, ','); // ignore the age value

      getline(inFS, element, ',');
      c.addPhone('H', element);

      getline(inFS, element);
      c.addPhone('C', element);

      contacts.push_back(c);
      numContactsAdded++;
    }

    result = "success: " + to_string(numContactsAdded) + " contacts added";
  }

  return result;
}

Contact *ContactList::getContact(int idx) { return &contacts.at(idx); }
