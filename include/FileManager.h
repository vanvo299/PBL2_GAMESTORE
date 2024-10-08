#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "D:\PBL2_GAMESTORE\include\Customer.h"
#include "D:\PBL2_GAMESTORE\include\Products.h"
#include <string>
#include <vector>
using namespace std;

class FileManager {
public:
    static Customer* loadCustomer(const std::string& fileCustomer, int &countCustomer); // Lưu khách hàng vào mảng động
    static void saveCustomer(const std::string& fileCustomer, Customer& customer); // Lưu khách hàng vào file


    static Products* loadSpecifications(const string &fileThongSoKyThuat, int &countProducts);
    static Products* loadProducts(const std::string& fileProducts, int &countProducts);
    static void saveProducts(const string fileProducts, Products* products, int &countProduct);

    static Products* loadOrder(const string& fileOrder, int& countOrder, int& capacity);
    static void saveOrder(const string& filename, Products* data, int& count);

    static void savePay(const string& filename, Products* pay, int& count, int customerID);
};

#endif