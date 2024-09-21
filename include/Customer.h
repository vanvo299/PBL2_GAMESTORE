#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std; 
class Customer {
private:
    int customerID;
    std::string customerName;
    std::string email;
    std::string phone;
    std::string userName;
    std::string password;
public:
    Customer(int customerID, std::string customerName, std::string email, std::string phone, std::string userName, std::string password);
    Customer();
    // Getter
    int getCustomerID();
    std::string getCustomerName();
    std::string getEmail();
    std::string getPhone();
    std::string getUserName();
    std::string getPassword();
    void resizeCustomerArray(Customer*& customers, int &size, const Customer& newCustomer);

    void setPassword(std::string &password);
    void setCustomerID(int customerID);
    // Verify login
    bool verifyLogin(const std::string &userName, const std::string &password);
    bool login(Customer *&loggedInCustomer);
    void registerAccount();
    void handlePostLogin(Customer*);

    void changePassword();
    void updateCustomerInfo();
    void displayCustomer();
};

#endif