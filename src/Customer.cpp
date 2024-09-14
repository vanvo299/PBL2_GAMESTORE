#include "D:\PBL2_GAMESTORE\include\Customer.h"
#include "D:\PBL2_GAMESTORE\include\FileManager.h"


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

void Customer::resizeCustomerArray(Customer*& customers, int &size, const Customer& newCustomer)
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

bool Customer::login()
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
        return true;
    }
    else return false;
}

void Customer::registerAccount()
{
    int customerSize;
    Customer* customers = FileManager::loadCustomer("D:\\PBL2_GAMESTORE\\text\\Customers.txt", customerSize);
    Customer *customer = new Customer;

    int newID = customerSize + 1;
    std::string name, email, phone, username, password;
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

// Cập nhật thông tin khách hàng (đang bị lỗi)
void Customer::updateCustomerInfo(Customer *customer)
{
    std::string name, email, phone;
    std::cin.ignore();
    std::cout << "Enter new name: ";
    getline(std::cin, name);
    std::cout << "Enter email: ";
    std::cin >> email;
    std::cout << "Enter phone: ";
    std::cin >> phone;

    // Cập nhật thông tin của khách hàng
    customer->customerName = name;
    customer->email = email;
    customer->phone = phone;

    // Lưu lại thông tin đã thay đổi
    int customerSize;
    Customer* updateCustomer = FileManager::loadCustomer("D:\\PBL2_GAMESTORE\\text\\Customers.txt", customerSize);

    // Tìm và cập nhật thông tin khách hàng 
    updateCustomer = customer;

    FileManager::saveCustomer("D:\\PBL2_GAMESTORE\\text\\Customers.txt", *updateCustomer); // Lưu vào file 

    std::cout << "Update info customer successfully !\n";
    delete [] updateCustomer;
}

// Hiển thị
void Customer::handlePostLogin(Customer* customer)
{
    
}