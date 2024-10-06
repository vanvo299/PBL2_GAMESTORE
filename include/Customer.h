#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std; 
class Customer {
private:
    // string customerName;
    string lastName;
    string firstName;
    string middleName;
    string email;
    string phone;
    string userName;
    string password;
protected:
    int customerID;
public:
    Customer(int customerID, string lastName, string middleName, string firstName, string email, string phone, string userName, string password);
    Customer();
    // Getter
    int getCustomerID();
    string getLastName();
    string getMiddleName();
    string getFirstName();
    string getEmail();
    string getPhone();
    string getUserName();
    string getPassword();
    void resizeCustomerArray(Customer*& customers, int &size, const Customer& newCustomer);

    void setPassword(string &password);
    void setCustomerID(int customerID);
    // Verify login
    bool verifyLogin(const string &userName, const string &password);

    int login(const string& username, const string &password, Customer *&loggedInCustomer);
    int login(Customer *&loggedInCustomer);

    void registerAccount();
    void registerAccount(string lastName, string middleName, string firstName, string email, string phone, string userName, string password);
    void handlePostLogin(Customer*);

    

    void changePassword();
    void updateCustomerInfo();
    void displayCustomer();
};

#endif