#include "D:\PBL2_GAMESTORE\include\Customer.h"
#include "D:\PBL2_GAMESTORE\include\FileManager.h"


Customer::Customer(int customerID, string lastName, string middleName, string firstName, std::string email, std::string phone, std::string userName, std::string password)
{
    this->customerID = customerID;
    this->lastName = lastName;
    this->middleName = middleName;
    this->firstName = firstName;
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

string Customer::getLastName()
{
    return lastName;
}

string Customer::getMiddleName()
{
    return middleName;
}

string Customer::getFirstName()
{
    return firstName;
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

// Đăng nhập
int Customer::login(Customer *&loggedInCustomer, int &ID)
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
    bool checkAdmin = false;
    for (int i = 0; i < customerSize; i++) {
        if (customers[i].verifyLogin(username, password)) {
            loggedInCustomer = &customers[i];
            found = true;
            break;
        }
    }
    // Nếu người login vào là Admin
        if (loggedInCustomer->getCustomerID() < 0) {
            checkAdmin = true;
        }
    if (checkAdmin && found) {
        cout << "Welcome to admin, " << loggedInCustomer->getLastName() << " " << loggedInCustomer->getMiddleName() << " " << loggedInCustomer->getFirstName() << "!\n";
        return 2;
    }
    else if (found) {
        ID = loggedInCustomer->getCustomerID();
        std::cout << "Login successful! Welcome, " << loggedInCustomer->getLastName() << " " << loggedInCustomer->getMiddleName() << " " << loggedInCustomer->getFirstName() << "!\n";
        return 1;
    }
    else return 0;
}

// Đăng kí tài khoản
void Customer::registerAccount()
{
    int customerSize;
    Customer* customers = FileManager::loadCustomer("D:\\PBL2_GAMESTORE\\text\\Customers.txt", customerSize);
    Customer *customer = new Customer;

    int newID = customerSize + 1;
    std::string lastName, middleName, firstName, email, phone, username, password;
    std::cout << "Enter your last name: ";
    std::cin.ignore();
    getline(std::cin, lastName);
    cout << "Enter your middle name: ";
    getline(cin, middleName);
    cout << "Enter your first name: ";
    getline(cin, firstName);
    std::cout << "Enter your email: ";
    std::cin >> email;
    std::cout << "Enter your phone: ";
    std::cin >> phone;
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;

    Customer newCustomer(newID, lastName, middleName, firstName, email, phone, username, password);
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
        // chỉ in ra thông tin của khách hàng
        if (customers[i].getCustomerID() < 0) {
            continue;
        }
        std::cout << customers[i].getCustomerID() << "\t" << customers[i].getLastName() << " " << customers[i].getMiddleName() << " " << customers[i].getFirstName() << "\t"
                  << "\t" << customers[i].getEmail() << "\t" << customers[i].getPhone() << std::endl;
    }
    delete [] customers;
}

// Cập nhật thông tin khách hàng
void Customer::updateCustomerInfo() {
    std::string newLastName, newMiddleName, newFirstName, newEmail, newPhone;
    std::cin.ignore(); // Để xử lý ký tự newline còn lại trong buffer

    std::cout << "Enter your last name: ";
    std::getline(std::cin, newLastName);
    cout << "Enter your middle name: ";
    getline(cin, newMiddleName);
    cout << "Enter your first name: ";
    getline(cin, newFirstName);
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
        std::string id, lastName, middleName, firstName, emailCustomer, phoneCustomer, username, password;

        // Phân tách dòng hiện tại bằng dấu phân cách '|'
        std::getline(iss, id, '|');
        std::getline(iss, lastName, '|');
        std::getline(iss, middleName, '|');
        std::getline(iss, firstName, '|');
        std::getline(iss, emailCustomer, '|');
        std::getline(iss, phoneCustomer, '|');
        std::getline(iss, username, '|');
        std::getline(iss, password);

        // Chỉ cập nhật thông tin của khách hàng hiện tại
        if (std::stoi(id) == this->getCustomerID()) {
            lastName = newLastName;
            middleName = newMiddleName;
            firstName = newFirstName;
            emailCustomer = newEmail;
            phoneCustomer = newPhone;
            found = true;
        }

        // Xây dựng lại nội dung file với giá trị đã cập nhật
        fileContent += id + '|' + lastName + '|' + middleName + '|' + firstName + '|' + emailCustomer + '|' + phoneCustomer + '|' + username + '|' + password + '\n';
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
                string id, lastName, middleName, firstName, email, phone, username, password;

                // Phan tich dong hien tai bang dau phan cach '|'
                getline(iss, id, '|');
                getline(iss, lastName, '|');
                getline(iss, middleName, '|');
                getline(iss, firstName, '|');
                getline(iss, email, '|');
                getline(iss, phone, '|');
                getline(iss, username, '|');
                getline(iss, password);

                if (stoi(id) == customerID) {
                    password = newPassword;
                    found = true;
                }

                // Xay dung lai noi dung file voi gia tri da cap nhat
                fileContent += id + '|' + lastName + '|' + middleName + '|' + firstName + '|' + email + '|' + phone + '|' + username + '|' + password + '\n'; 
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