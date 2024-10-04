#include "D:\PBL2_GAMESTORE\include\FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

Customer* FileManager::loadCustomer(const std::string& fileCustomer, int &countCustomer)
{
    std::ifstream file(fileCustomer);
    Customer* customers = NULL;
    countCustomer = 0;

    if (file.is_open()) {
        std::string line;
        // Đếm số lượng khách hàng
        while(getline(file, line)) {
            ++countCustomer;
        }

        // Đếm xong và quay lại đầu file và cấp phát mảng và ghi dữ liệu vào mảng
        file.clear();
        file.seekg(0, std::ios::beg); // seekg dùng để di chuyển con trỏ về vị trí 0 đầu file
        customers = new Customer[countCustomer];
        int idx = 0;

        while(getline(file, line)) {
            std::istringstream iss(line);
            std::string customerID_str, lastName, middleName, firstName, email, phone, userName, password;

            // Tách các thành phần trong dòng bằng dấu |
            std::getline(iss, customerID_str, '|');
            std::getline(iss, lastName, '|');
            std::getline(iss, middleName, '|');
            std::getline(iss, firstName, '|');
            std::getline(iss, email, '|');
            std::getline(iss, phone, '|');
            std::getline(iss, userName, '|');
            std::getline(iss, password, '|');

            // Chuyển ID từ chuỗi thành số nguyên
            int customerID = std::stoi(customerID_str);

            // Tạo Customer và lưu vào mảng
            customers[idx++] = Customer(customerID, lastName, middleName, firstName, email, phone, userName, password);
        }
    }
    return customers;
}

// Hàm nạp danh sách sản phẩm vào trong mảng
Products* FileManager::loadSpecifications(const string &fileThongSoKyThuat, int &countProducts)
{
    ifstream file(fileThongSoKyThuat);
    if (!file.is_open()) {
        cerr << "Cannot open file!" << endl;
        return NULL;
    }

    Products *products = NULL;
    string line;
    countProducts = 0;
    bool isProductStarted = false;
    string productData;

    // Đọc số lượng sản phẩm trước
    while (getline(file, line)) {
        if (line == "*") {
            if (!isProductStarted) {
                // Bắt đầu sản phẩm mới
                isProductStarted = true;
                countProducts++;
            } else {
                // Kết thúc sản phẩm hiện tại
                isProductStarted = false;
            }
        }
    }

    // Cấp phát mảng sản phẩm
    file.clear();
    file.seekg(0, ios::beg); // Quay lại đầu file
    products = new Products [countProducts];
    int idx = 0;
    isProductStarted = false;

    while (getline(file, line)) {
        if (line == "*") {
            if (isProductStarted) {
                // Đã đọc xong một sản phẩm, xử lý dữ liệu sản phẩm
                istringstream in(productData);
                string productID_str, nameProduct, genre, priceProduct_str, manufacturer, operatingSystem, specifications, counts;

                // Đảm bảo tách đúng các phần của sản phẩm
                if (getline(in, productID_str, '|') &&
                    getline(in, nameProduct, '|') &&
                    getline(in, genre, '|') &&
                    getline(in, priceProduct_str, '|') &&
                    getline(in, manufacturer, '|') &&
                    getline(in, operatingSystem, '|') &&
                    getline(in, specifications, '|')) {

                    // Chuyển đổi kiểu dữ liệu
                    try {
                        int productID = stoi(productID_str);
                        double priceProduct = stod(priceProduct_str);

                        // Gán dữ liệu cho sản phẩm
                        products[idx++] = Products(productID, nameProduct, genre, priceProduct, manufacturer, operatingSystem, specifications);
                    } catch (const invalid_argument& e) {
                        cerr << "Error converting data: " << e.what() << endl;
                    }
                }

                // Reset dữ liệu cho sản phẩm tiếp theo
                productData.clear();
                isProductStarted = false;
            } else {
                // Bắt đầu sản phẩm mới
                isProductStarted = true;
            }
        } else if (isProductStarted) {
            // Thêm dòng dữ liệu vào sản phẩm
            productData += line + "\n";
        }
    }
    return products;
}

void FileManager::saveCustomer(const std::string& fileCustomer, Customer& customer)
{
    std::ofstream file(fileCustomer, std::ios::app);
    if (file.is_open()) {
        file << customer.getCustomerID() << '|'
             << customer.getLastName() << '|'
             << customer.getMiddleName() << '|'
             << customer.getFirstName() << '|'
             << customer.getEmail() << '|'
             << customer.getPhone() << '|'
             << customer.getUserName() << '|'
             << customer.getPassword() << std::endl;
    }
}

Products* FileManager::loadProducts(const std::string& fileProducts, int &countProducts)
{
    std::ifstream file(fileProducts);
    Products *products = NULL;
    countProducts = 0;

    if (file.is_open()) {
        std::string line;
        // Đếm số lượng khách hàng
        while(getline(file, line)) {
            ++countProducts;
        }

        // Đếm xong và quay lại đầu file và cấp phát mảng và ghi dữ liệu vào mảng
        file.clear();
        file.seekg(0, std::ios::beg); // seekg dùng để di chuyển con trỏ về vị trí 0 đầu file
        products = new Products[countProducts];
        int idx = 0;

        while(getline(file, line)) {
            std::istringstream iss(line);
            std::string productID_str, nameProduct, genre, priceProduct_str, manufacturer, operatingSystem;

            // Tách các thành phần trong dòng bằng dấu |
            std::getline(iss, productID_str, '|');
            std::getline(iss, nameProduct, '|');
            std::getline(iss, genre, '|');
            std::getline(iss, priceProduct_str, '|');
            std::getline(iss, manufacturer, '|');
            std::getline(iss, operatingSystem);
           

            // Chuyển ID từ chuỗi thành số nguyên
            int productID = std::stoi(productID_str);
            double priceProduct = stod(priceProduct_str);
            // Tạo Customer và lưu vào mảng
            products[idx++] = Products(productID, nameProduct, genre, priceProduct, manufacturer, operatingSystem);
        }
    }
    return products;
}