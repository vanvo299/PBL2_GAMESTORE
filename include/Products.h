#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <iostream>
#include <string>

using namespace std;

class Products {
    private:
        int productID; // Mã sản phẩm
        string nameProduct; // Tên sản phẩm
        string genre; // thể loại của sản phẩm
        double priceProduct; // Giá
        string manufacturer; // nhà sản xuất
        string operatingSystem; // Hệ điều hành
        string specifications; // Thông số kĩ thuật
    public:
        Products(int productID, string nameProduct, string genre, double priceProduct, string manufacturer, string operatingSystem, string specifications);
        Products();
        ~Products();
        // getter
        int getProductID();
        string getNameProduct();
        string getGenre();
        double getPriceProduct();
        string getManufacturer();
        string getOperatingSystem();
        string getSpecifications();
        
        // setter
        void setProductID(int productID);
        void setNameProduct(string nameProduct);
        void setGenre(string genre);
        void setPriceProduct(double priceProduct);
        void setManufacturer(string manufacturer);
        void setOperatingSystem(string operatingSystem);

        void displayProducts();
};
#endif