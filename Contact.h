// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <string>
// #include <algorithm>

using namespace std;


#ifndef CONTACT_H
#define CONTACT_H


class Contact {

  struct PhoneNumber {
    char phoneType;				// W(ork), H(ome), C(ell)
    string number;
  };

  public:

    // constructors
    Contact(char contactType, string firstName, string lastName);


    // getters
    char getContactType() {return contactType;};
    string getFirstName() {return firstName;};
		string getLastName() {return lastName;};
    string getState() {return state;};
    string getEmail() {return email;};
    string getDateOfBirth() {return dateOfBirth;};
    vector<string> getPhoneNumbers();

    // setters
    void setContactType (char contactType) {this->contactType = contactType;};
    void setFirstName (string firstName) {this->firstName = firstName;};
    void setLastName (string lastName) {this->lastName = lastName;};
    void setEmail (string email) {this->email = email;};
    void setDateOfBirth (string dateOfBirth) {this->dateOfBirth = dateOfBirth;};


    // other public functions

    string getName();
    string getAddress();
    void setAddress(int streetNumber, string streetName, 
                        string city, string state, int postalCode);
    string addPhone (char phoneType, string number);
    string deletePhone (int idx);
    string getAsString();
    string tester();

    friend bool operator<(Contact lhs, Contact rhs);


  private:
    char contactType;
    string firstName, lastName,streetName,city,state,email, dateOfBirth;
    int streetNumber, postalCode;
    vector<PhoneNumber> phoneNumbers;

    string getLabelForType (char type);
    
};

#endif