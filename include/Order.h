#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;


class Data {
public:
    int productID; // mã sản phẩm
    string nameProduct; // tên sản phẩm
    string genre; // thể loại của sản phẩm
    string manufacturer; // nhà sản xuất
    string operatingSystem; // hệ điều hành
    double priceProduct; // giá
    int amount; // số lượng mua cùng 1 món hàng của 1 người
    Data() : productID(0), nameProduct(""), genre(""), manufacturer(""), operatingSystem(""), priceProduct(0.0), amount(0) {}
    Data(int ID, const string& name, const string& gen, const string& manu, const string& oper, double p, int n)
        : productID(ID), nameProduct(name), genre(gen), manufacturer(manu), operatingSystem(oper), priceProduct(p), amount(n) {}
};

class Order {
    Data* data;  // con trỏ động chứ danh sách
    int capacity; // số lượng tối đa
    int count;    // số lượng hiện tại
    double totalPrice; // giá tiền của đơn hàng

public:
    Order(int cap = 10);
    Order(const Order& other);
    Order& operator=(const Order& other);
    ~Order();
    void addData(int ID, const string& name, const string& gen, const string& manu, const string& oper, double p, int n); // thêm vào 
    void deleteData(int ID); // xóa
    void increaseCapacity(); // tăng sức chứa
    void displayOrder() const; // in ra
    void saveToFile(const string& filename) const; // lưu vào file text
    int findData(int& ID) const; // tìm kiếm đơn hàng theo ID sản phẩm
    int findData(const string& name) const; // tìm kiếm đơn hàng theo tên sản phẩm
    void updateData(int&, const string&, const string&, const string&, const string&, double); //cập nhập thông tin đơn hàng khí có sự thay đổi
    void clearOrder(); // xóa toàn bộ đơn hàng
    void sortOrderByPrice(); //sắp xếp theo giá tăng dần

};

#endif