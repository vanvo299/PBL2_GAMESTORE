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
        double priceProduct; // giá
        string manufacturer; // nhà sản xuất
        string operatingSystem; // hệ điều hành
        string specifications; // Thông số kĩ thuật
        int Count; // số lượng sản phẩm
    public:
        Products();
        Products(int productID, string nameProduct, string genre, double priceProduct, string manufacturer, string operatingSystem, int Count);
        Products(int ProductID, string specifications);
        Products(int productID, string nameProduct, string genre, double priceProduct, string manufacturer, string operatingSystem, string specifications, int Count);
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

        // display
        void displayProducts(); // Hiển thị ra sản phẩm
        void displaySpecification(int productID); // Hiển thị thông số kỹ thuật chi tiết của sản phẩm

        friend ostream& operator<<(ostream& out, const Products& product);
};
#endif