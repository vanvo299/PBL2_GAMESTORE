#ifndef ADMIN_H
#define ADMIN_H

#include "Customer.h"
#include "Order.h"
#include "Products.h"
#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Admin {
    public:
        Admin();
        ~Admin();
        void addProduct();
        void editProduct();
        void deleteProduct();
};

#endif