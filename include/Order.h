#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "D:\PBL2_GAMESTORE\include\Products.h"
#include "D:\PBL2_GAMESTORE\include\Customer.h"
using namespace std;

class Product : public Products{       
    public:
        static Products* products;
        static int countProduct;
        Product();
        Product(int);
        Product(int, string, string, string, string, double, int);
        Product(int, string, string, double, string, string, int);
        ~Product();
        static void loadProducts(const std::string& fileProducts, int& countProducts);
        Product& operator = (const Product&);
        int getCountP();
        void displayProduct();
        void saveToFile(const string fileProducts);
};

class Order : public Customer, public Product {
    Products* data;  // con trỏ động chứ danh sách
    int capacity; // số lượng tối đa
    int count;    // số lượng hiện tại
    static int customerID; // ID của khách hàng
public:
    Order(int productID, string nameProduct, string genre, double priceProduct, string manufacturer, string operatingSystem, int count);

    Order(int capacity = 10);
    Order(const Order& other);
    Order& operator=(const Order& other);
    ~Order();
    // lấy ID của khách hàng
    void setID(int ID);
    // lấy Order trong file
    Products* loadOrder(const string &fileOrder, int &count, int &capacity);

    // Order* loadOrder(const string &fileOrder, int& countOrder); // Load dữ liệu thông tin giỏ hàng của từng khách hàng

    void update(){
        data = loadOrder("D:\\PBL2_GAMESTORE\\text\\Orders.txt", count, capacity);
    }
    // thêm vào
    void addData(int ID);  
    void addData(string name);
    // xóa
    void deleteData(int ID); 
    void deleteData(string name);
    // tăng sức chứa
    void increaseCapacity();
    // in ra
    void displayOrder(); 
    // lưu vào file text
    void saveToFile(const string& filename) const; 
    // tìm kiếm đơn hàng trong order
    int findData(int& ID) const;
    int findData(const string& name) const;
    //cập nhập thông tin đơn hàng khí có sự thay đổi
    void updateData(int&, const string&, const string&, const string&, const string&, double, int); 
    void clearOrder(); // xóa toàn bộ đơn hàng
    void sortOrderByPrice(); //sắp xếp theo giá tăng dần


    // lưu vào file Pay.txt
    void saveToFile(const string& filename, int id) const; 
    void change(int id);
    void change();
    // thanh toán
    void pay();
};

#endif