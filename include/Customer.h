#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <string>

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
    
    // Verify login
    bool verifyLogin(const std::string &userName, const std::string &password);

    void displayCustomer();
};

#endif