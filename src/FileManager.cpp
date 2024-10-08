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
                    getline(in, specifications, '|')) {

                    // Chuyển đổi kiểu dữ liệu
                    try {
                        int productID = stoi(productID_str);
                        // Gán dữ liệu cho sản phẩm
                        products[idx++] = Products(productID, specifications);
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
            std::string productID_str, nameProduct, genre, priceProduct_str, manufacturer, operatingSystem, count_str;

            // Tách các thành phần trong dòng bằng dấu |
            std::getline(iss, productID_str, '|');
            std::getline(iss, nameProduct, '|');
            std::getline(iss, genre, '|');
            std::getline(iss, priceProduct_str, '|');
            std::getline(iss, manufacturer, '|');
            std::getline(iss, operatingSystem, '|');
            std::getline(iss, count_str);
           
            // Chuyển ID từ chuỗi thành số nguyên
            int productID = std::stoi(productID_str);
            int count = std::stoi(count_str);
            double priceProduct = std::stod(priceProduct_str);
            // Tạo Customer và lưu vào mảng
            products[idx++] = Products(productID, nameProduct, genre, priceProduct, manufacturer, operatingSystem, count);
        }
    }
    return products;
}
void FileManager::saveProducts(const string fileProducts, Products* products, int& countProduct){
    ofstream outFile(fileProducts, ios::out);
    if (outFile.is_open()) {
        for(int i = 0; i < countProduct; i++){
            outFile << products[i].getProductID() << "|"
                << products[i].getNameProduct() << "|"
                << products[i].getGenre() << "|"
                << products[i].getPriceProduct() << "|"
                << products[i].getManufacturer() << "|"
                << products[i].getOperatingSystem() << "|"
                << products[i].getCount() << endl;
        }
        outFile.close();
    }
    else {
        cout << "Unable to open file " << fileProducts << endl;
    }
}


Products* FileManager::loadOrder(const string &fileOrder, int& countOrder, int& capacity)
{
    ifstream inFile(fileOrder);
    countOrder = 0;
    Products* orders = nullptr; // Sử dụng nullptr thay cho NULL

    if (!inFile.is_open()) {
        cout << "Could not open the file. \n";
        return nullptr;
    }

    string line;
    while (getline(inFile, line)) {
        ++countOrder;
    }
    capacity = (countOrder / 10 + 1) * 10;
    inFile.clear();
    inFile.seekg(0, ios::beg);

    orders = new (std::nothrow) Products[capacity]; // Sử dụng std::nothrow để tránh ngoại lệ
    if (orders == nullptr) {
        std::cerr << "Memory allocation failed." << std::endl;
        return nullptr; // Trả về nullptr nếu cấp phát thất bại
    }

    int index = 0;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string productID_str, nameProduct, genre, priceProduct_str, manufacturer, operatingSystem, count_str;

        getline(iss, productID_str, '|');
        getline(iss, nameProduct, '|');
        getline(iss, genre, '|');
        getline(iss, priceProduct_str, '|');
        getline(iss, manufacturer, '|');
        getline(iss, operatingSystem, '|');
        getline(iss, count_str);
        
        try{
            int productID = stoi(productID_str);
            double priceProduct = stod(priceProduct_str);
            int count = stoi(count_str);
            
            // Đảm bảo chỉ số không vượt quá countOrder
            if (index < countOrder) {
                orders[index++] = Products(productID, nameProduct, genre, priceProduct, manufacturer, operatingSystem, count);
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid data in file: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Number out of range in file: " << e.what() << std::endl;
        }
        
    }
    return orders; // Chỉ cần trả về orders mà không cần delete ở đây
}
void FileManager::saveOrder(const string& filename, Products* data, int& count){
    ofstream outFile(filename, ios:: out);
    if (outFile.is_open()) {
        for (int i = 0; i < count; i++) {
            // outFile << i + 1
            outFile << data[i].getProductID() << "|"
                    << data[i].getNameProduct() << "|"
                    << data[i].getGenre() << "|"
                    << data[i].getPriceProduct() << "|"
                    << data[i].getManufacturer() << "|"
                    << data[i].getOperatingSystem() << "|"
                    << data[i].getCount() << endl;
        }
        outFile.close();
    }
    else {
        cout << "Unable to open file " << filename << endl;
    }
}


void FileManager::savePay(const string& filename, Products* pay, int& count, int customerID){
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "*" << endl;
        outFile << customerID << "|";
        for (int i = 0; i < count; i++) {
            // outFile << i + 1
            outFile << pay[i].getProductID() << "|"
                    << pay[i].getNameProduct() << "|"
                    << pay[i].getGenre() << "|"
                    << pay[i].getPriceProduct() << "|"
                    << pay[i].getManufacturer() << "|"
                    << pay[i].getOperatingSystem() << "|"
                    << pay[i].getCount() << endl;
        }
        outFile << "*" << endl;
        outFile.close();
    }
    else {
        cout << "Unable to open file " << filename << endl;
    }
}