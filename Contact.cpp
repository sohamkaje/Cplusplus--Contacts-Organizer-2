#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Contact.h"

Contact::Contact(char contactType, string firstName, string lastName) {
  this->contactType = contactType;
  this->firstName = firstName;
  this->lastName = lastName;
}

string Contact::getName() { return lastName + ", " + firstName; }

string Contact::getAddress() {
  string result = "";
  result += to_string(streetNumber) + " " + streetName + ", ";
  result += city + ", " + state + " " + to_string(postalCode);

  return result;
}

void Contact::setAddress(int streetNumber, string streetName, string city,
                         string state, int postalCode) {
  this->streetNumber = streetNumber;
  this->streetName = streetName;
  this->city = city;
  this->state = state;
  this->postalCode = postalCode;
}

string Contact::addPhone(char phoneType, string number) {

  string result;

  if (phoneType == 'C' || phoneType == 'W' || phoneType == 'H') {

    PhoneNumber newPhone;
    newPhone.phoneType = phoneType;
    newPhone.number = number;

    phoneNumbers.push_back(newPhone);

    result = "success: added number " + number + " ";

    if (phoneType == 'H') {
      result += "Home";
    } else if (phoneType == 'C') {
      result += "Cell";
    } else if (phoneType == 'W') {
      result += "Work";
    }

  } else {
    result = "failure: invalid phone type - ";
    result.push_back(phoneType);
  }

  return result;
}

string Contact::deletePhone(int idx) {
  string result, numberToDelete;

  if (idx < phoneNumbers.size()) {
    numberToDelete = phoneNumbers.at(idx).number;
    phoneNumbers.erase(phoneNumbers.begin() + idx);
    result = "success: deleted phone " + numberToDelete;
  } else {
    result = "failure: unable to delete phone " + to_string(idx);
  }

  return result;
}

string Contact::getAsString() {

  string result = getName() + "\n";
  result += getLabelForType(contactType) + "\n";
  result += getAddress() + "\n";
  result += getDateOfBirth() + "\n";
  result += getEmail() + "\n";

  for (PhoneNumber pn : phoneNumbers) {
    result += getLabelForType(pn.phoneType) + ": " + pn.number + "\n";
  }

  return result;
}

string Contact::getLabelForType(char type) {
  string result;

  switch (type) {
  case 'P':
    result = "Personal";
    break;
  case 'W':
    result = "Work";
    break;
  case 'C':
    result = "Cell";
    break;
  case 'H':
    result = "Home";
    break;
  default:
    result = "Unknown type";
  }

  return result;
}

vector<string> Contact::getPhoneNumbers() {
  vector<string> numbers;

  for (PhoneNumber pn : phoneNumbers) {
    numbers.push_back(getLabelForType(pn.phoneType) + " " + pn.number);
  }

  return numbers;
}

// Less-than (<) operator for two Contact objects
bool operator<(Contact lhs, Contact rhs) {
  return lhs.getName() < rhs.getName();
}