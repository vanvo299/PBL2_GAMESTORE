#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "D:\PBL2_GAMESTORE\include\Customer.h"
#include "D:\PBL2_GAMESTORE\include\Order.h"
#include "D:\PBL2_GAMESTORE\include\Products.h"
#include <string>
using namespace std;
class FileManager {
public:
    static Customer* loadCustomer(const std::string &fileCustomer, int &countCustomer); // Lưu khách hàng vào mảng động
    static Products* loadProducts(const string &fileProduct, int &countProducts);
    static void saveCustomer(const std::string& fileCustomer, Customer& customer); // Lưu khách hàng vào file
    // static void saveOrders(const std::string &fileOrders, const Order* orders, int orderCount);
};

#endif