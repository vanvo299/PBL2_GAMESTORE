#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Customer.h"
#include "Order.h"
#include "Products.h"
#include <string>
using namespace std;
class FileManager {
public:
    static Customer* loadCustomer(const std::string& fileCustomer, int &countCustomer); // Lưu khách hàng vào mảng động
    static Products* loadSpecifications(const string &fileThongSoKyThuat, int &countProducts);
    static void saveCustomer(const std::string& fileCustomer, Customer& customer); // Lưu khách hàng vào file
    // static void saveOrders(const std::string &fileOrders, const Order* orders, int orderCount);
    static Products* loadProducts(const std::string& fileProducts, int &countProducts);

};

#endif