#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Customer.h"
#include "Game.h"
#include "Order.h"
#include "Products.h"
#include <string>
using namespace std;
class FileManager {
public:
    static Customer* loadCustomer(const std::string &fileCustomer, int &countCustomer); // Lưu khách hàng vào mảng động
    static Game* loadGames(const std::string &fileGame, int& countGames); // Lưu game vào mảng động
    static Products* loadProducts(const string &fileProduct, int &countProducts);
    static void saveCustomer(const std::string& fileCustomer, Customer& customer); // Lưu khách hàng vào file
    // static void saveOrders(const std::string &fileOrders, const Order* orders, int orderCount);
};

#endif