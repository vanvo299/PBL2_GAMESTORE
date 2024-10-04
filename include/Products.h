#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <iostream>
#include <string>

using namespace std;


class Products{
    protected:
        int productID; // mã sản phẩm
        string nameProduct; // tên sản phẩm
        string genre; // thể loại của sản phẩm
        string manufacturer; // nhà sản xuất
        string operatingSystem; // hệ điều hành
        double priceProduct; // giá
        string specifications; // Thông số kĩ thuật
        int Count; // số lượng sản phẩm
    public:
        Products();
        Products(int, string, string, string, string, double, string, int);
        Products(int, string, string, string, string, double, int);
        ~Products();
        // getter
        int getProductID();
        string getNameProduct();
        string getGenre();
        double getPriceProduct();
        string getManufacturer();
        string getOperatingSystem();
        string getSpecifications();
        int getCount();
        
        // setter
        void setProductID(int productID);
        void setNameProduct(string nameProduct);
        void setGenre(string genre);
        void setPriceProduct(double priceProduct);
        void setManufacturer(string manufacturer);
        void setOperatingSystem(string operatingSystem);
        void setCount(int count);
        void displayProducts();
};
#endif