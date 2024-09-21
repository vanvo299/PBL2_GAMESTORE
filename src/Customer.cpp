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

void Customer::setPassword(string &password)
{
    this->password = password;
}

void Customer::setCustomerID(int customerID) 
{
    this->customerID = customerID;
}
bool Customer::verifyLogin(const std::string &userName, const std::string &password)
{
    return (this->userName == userName && this->password == password);
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

bool Customer::login(Customer *&loggedInCustomer)
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
            loggedInCustomer = &customers[i];
            found = true;
            break;
        }
    }
    if (found) {
        std::cout << "Login successful! Welcome, " << loggedInCustomer->getCustomerName() << "!\n";
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

// Cập nhật thông tin khách hàng
void Customer::updateCustomerInfo() {
    std::string newName, newEmail, newPhone;
    std::cin.ignore(); // Để xử lý ký tự newline còn lại trong buffer

    std::cout << "Enter new name: ";
    std::getline(std::cin, newName);

    std::cout << "Enter new email: ";
    std::cin >> newEmail;

    std::cout << "Enter new phone: ";
    std::cin >> newPhone;

    // Đọc file và cập nhật thông tin khách hàng
    std::ifstream fileIn("D:\\PBL2_GAMESTORE\\text\\Customers.txt");
    if (!fileIn.is_open()) {
        std::cout << "Unable to open file for reading.\n";
        return;
    }

    std::string line, fileContent;
    bool found = false;

    // Đọc từng dòng và xử lý
    while (std::getline(fileIn, line)) {
        std::istringstream iss(line);
        std::string id, customerName, emailCustomer, phoneCustomer, username, password;

        // Phân tách dòng hiện tại bằng dấu phân cách '|'
        std::getline(iss, id, '|');
        std::getline(iss, customerName, '|');
        std::getline(iss, emailCustomer, '|');
        std::getline(iss, phoneCustomer, '|');
        std::getline(iss, username, '|');
        std::getline(iss, password);

        // Chỉ cập nhật thông tin của khách hàng hiện tại
        if (std::stoi(id) == this->getCustomerID()) {
            customerName = newName;
            emailCustomer = newEmail;
            phoneCustomer = newPhone;
            found = true;
        }

        // Xây dựng lại nội dung file với giá trị đã cập nhật
        fileContent += id + '|' + customerName + '|' + emailCustomer + '|' + phoneCustomer + '|' + username + '|' + password + '\n';
    }
    fileIn.close();

    if (!found) {
        std::cout << "Customer not found.\n";
        return;
    }

    // Ghi đè lại file với nội dung mới
    std::ofstream fileOut("D:\\PBL2_GAMESTORE\\text\\Customers.txt", std::ios::trunc);
    if (!fileOut.is_open()) {
        std::cout << "Unable to open file for writing.\n";
        return;
    }

    fileOut << fileContent;
    fileOut.close();

    std::cout << "Update information successfully.\n";
}

// Thay đổi mật khẩu người dùng 
void Customer::changePassword()
{
    string oldPassword, newPassword, confirmPassword;
    std::cout << "Enter the old password: "; cin >> oldPassword;
    
    if (oldPassword != this->getPassword()) {
        cout << "Old password is incorrect. \n";
        return;
    }
    if (oldPassword == this->getPassword()) {
        cout << "Enter the new password: "; cin >> newPassword;
        cout << "Enter the confirm password: "; cin >> confirmPassword;

        if (newPassword != confirmPassword) {
            cout << "Confirmation password is incorrect. \n";
            return;
        } else {
            ifstream fileIn("D:\\PBL2_GAMESTORE\\text\\Customers.txt");
            if (!fileIn.is_open()) {
                cout << "Unable to open file for reading. \n";
                return;
            }

            string line, fileContent;
            bool found = false;

            // Doc tung dong va xu ly
            while(getline(fileIn, line)) {
                istringstream iss(line);
                string id, customerName, email, phone, username, password;

                // Phan tich dong hien tai bang dau phan cach '|'
                getline(iss, id, '|');
                getline(iss, customerName, '|');
                getline(iss, email, '|');
                getline(iss, phone, '|');
                getline(iss, username, '|');
                getline(iss, password);

                if (stoi(id) == customerID) {
                    password = newPassword;
                    found = true;
                }

                // Xay dung lai noi dung file voi gia tri da cap nhat
                fileContent += id + '|' + customerName + '|' + email + '|' + phone + '|' + username + '|' + password + '\n'; 
            }
            fileIn.close();
            if (!found) {
                cout << "Not found customer. \n";
                return;
            }

            // Ghi de lai file voi noi dung moi
            ofstream fileOut("D:\\PBL2_GAMESTORE\\text\\Customers.txt", ios::trunc);
            if (!fileOut.is_open()) {
                cout << "Unable to open file for writing. \n";
                return;
            }
            fileOut << fileContent;
            fileOut.close();
            cout << "Change password successfully. \n";
        }
    }   
}
// Hiển thị
void Customer::handlePostLogin(Customer* customer)
{
    
}