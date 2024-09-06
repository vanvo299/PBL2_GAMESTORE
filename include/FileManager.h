#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Customer.h"
#include "Game.h"
#include "Order.h"
#include <string>

class FileManager {
public:
    static Customer* loadCustomer(const std::string &fileCustomer, int &countCustomer);
    static Game* loadGames(const std::string &fileGame, int& countGames);
    static void saveCustomer(const std::string& fileCustomer, Customer& customer);
    // static void saveOrders(const std::string &fileOrders, const Order* orders, int orderCount);
};

#endif