#include "D:\PBL2_GAMESTORE\include\Customer.h"
#include "D:\PBL2_GAMESTORE\include\FileManager.h"
#include "D:\PBL2_GAMESTORE\include\Game.h"
#include <iostream>

void resizeCustomerArray(Customer*& customers, int &size, const Customer& newCustomer)
{
    // Tạo mảng mới với kích thước lớn hơn
    Customer* newCustomers = new Customer[size + 1];

    for (int i = 0; i < size; i++) {
        newCustomers[i] = customers[i];
    }

    // Thêm khách hàng mới
    newCustomers[size] = newCustomer;
    
    // Giải phóng bộ nhớ và cập nhật mảng và kích thước
    delete [] customers;

    // Gán mảng mới và tăng kích thước
    customers = newCustomers;
    ++size;
}

int main()
{
    int customerSize;
    Customer* customers = FileManager::loadCustomer("D:\\PBL2_GAMESTORE\\text\\Customers.txt", customerSize);

    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    Customer* customer = nullptr;
    bool found = false;

    for (int i = 0; i < customerSize; i++) {
        if (customers[i].verifyLogin(username, password)) {
            customer = &customers[i];
            found = true;
            break;
        }
    }

    if (found) {
        std::cout << "Login successful! Welcome, " << customer->getCustomerName() << "!\n";
    } else {
        std::cout << "Account not found. Do you want to create a new account? (y/n): ";
        char choice;
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            int newID = customerSize + 1;
            std::string name, email, phone;
            std::cout << "Enter your name: ";
            std::cin.ignore();
            getline(std::cin, name);
            std::cout << "Enter your email: ";
            std::cin >> email;
            std::cout << "Enter your phone: ";
            std::cin >> phone;
            std::cout << "Enter your username: ";
            std::cin >> username;
            std::cout << "Enter your password: ";
            std::cin >> password;

            Customer newCustomer(newID, name, email, phone, username, password);
            resizeCustomerArray(customers, customerSize, newCustomer); // Thêm khách hàng mới vào mảng động 
            FileManager::saveCustomer("D:\\PBL2_GAMESTORE\\text\\Customers.txt", newCustomer); // Lưu vào file 

            std::cout << "Account created successfully!\n";
            customer = &customers[customerSize - 1];
        } else {
            std::cout << "Login failed.\n";
            delete [] customers;
            return 0;
        }
    }

    std::cout << "Welcome, " << customer->getCustomerName() << "!\n";

    Game *games = new Game;
    games->displayGame();

    std::cout << "\n\n";
    Customer *khachHang = new Customer;
    khachHang->displayCustomer();

    delete khachHang;
    delete games;
    delete [] customers;
    return 0;
}
