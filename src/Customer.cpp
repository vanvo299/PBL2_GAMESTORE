#include "D:\PBL2_GAMESTORE\include\Customer.h"
#include "D:\PBL2_GAMESTORE\include\FileManager.h"
#include <iostream>

Customer::Customer(int customerID, std::string customerName, std::string email, std::string phone, std::string userName, std::string password)
{
    this->customerID = customerID;
    this->customerName = customerName;
    this->email = email;
    this->phone = phone;
    this->userName = userName;
    this->password = password;
}

Customer::Customer() {};

int Customer::getCustomerID()
{
    return customerID;
}

std::string Customer::getCustomerName()
{
    return customerName;
}

std::string Customer::getEmail()
{
    return email;
}

std::string Customer::getPhone()
{
    return phone;
}

std::string Customer::getUserName()
{
    return userName;
}

std::string Customer::getPassword()
{
    return password;
}

bool Customer::verifyLogin(const std::string &userName, const std::string &password)
{
    if (this->userName != userName && this->password != password) {
        return false;
    }
    return true;
}

void Customer::displayCustomer()
{
    int customerSize;
    Customer *customers = FileManager::loadCustomer("D:\\PBL2_GAMESTORE\\text\\Customers.txt", customerSize);

    if (customers == NULL || customerSize == 0) {
        std::cout << "No customer available. " << std::endl;
        return;
    }

    // Hiển thị danh sách khách hàng
    std::cout << "List customers \n";
    std::cout << "customerID\t" << "customerName\t" << "Email\t" << "Phone\t" << std::endl;
    for (int i = 0; i < customerSize; i++) {
        std::cout << customers[i].getCustomerID() << "\t" << customers[i].getCustomerName() 
                  << "\t" << customers[i].getEmail() << "\t" << customers[i].getPhone() << std::endl;
    }
    delete [] customers;
}