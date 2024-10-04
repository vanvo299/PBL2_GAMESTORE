#include "D:\PBL2_GAMESTORE\include\Products.h"
#include "D:\PBL2_GAMESTORE\include\FileManager.h"
#include <iomanip>

Products::Products(int ID, string name, string gen, string manu, string oper, double price, string speci, int count){
    this->productID = ID;
    this->nameProduct = name;
    this->genre = gen;
    this->manufacturer = manu;
    this->operatingSystem = oper;
    this->priceProduct = price;
    this->specifications = speci;
    this->Count = count;
}

Products::Products(int ID, string name, string gen, string manu, string oper, double price, int count){
    this->productID = ID;
    this->nameProduct = name;
    this->genre = gen;
    this->manufacturer = manu;
    this->operatingSystem = oper;
    this->priceProduct = price;
    this->Count = count;
}

Products::Products(int productID, string nameProduct, string genre, double priceProduct, string manufacturer, string operatingSystem)
{
    this->productID = productID;
    this->nameProduct = nameProduct;
    this->genre = genre;
    this->priceProduct = priceProduct;
    this->manufacturer = manufacturer;
    this->operatingSystem = operatingSystem;
}

Products::Products(int productID, string specifications)
{
    this->productID = productID;
    this->specifications = specifications;
}

Products::Products(){}

Products::~Products(){}

int Products::getProductID(){
    return productID;
}

string Products::getNameProduct(){
    return nameProduct;
}

string Products::getGenre(){
    return genre;
}

double Products::getPriceProduct(){
    return priceProduct;
}


string Products::getManufacturer(){
    return manufacturer;
}

string Products::getOperatingSystem(){
    return operatingSystem;
}

string Products::getSpecifications(){
    return specifications;
}

int Products::getCount(){
    return Count;
}

void Products::setProductID(int productID){
    this->productID = productID;
}

void Products::setNameProduct(string nameProduct){
    this->nameProduct = nameProduct;
}
void Products::setGenre(string genre){
    this->genre = genre;
}
void Products::setPriceProduct(double priceProduct){
    this->priceProduct = priceProduct;
}
void Products::setManufacturer(string manufacturer){
    this->manufacturer = manufacturer;
}
void Products::setOperatingSystem(string operatingSystem){
    this->operatingSystem = operatingSystem;
}
void Products::setCount(int count){
    this->Count = count;
}

ostream& operator<<(ostream& out, const Products& product) 
{
    out << product.productID << "|" 
            << product.nameProduct << "|"
            << product.genre << "|"
            << product.priceProduct << "|"
            << product.manufacturer << "|"
            << product.operatingSystem;
    return out;
}

// Hiển thị thông tin của sản phẩm // Author: Vo
void Products::displayProducts()
{
    int productSize;
    Products *products = FileManager::loadProducts("D:\\PBL2_GAMESTORE\\text\\Products.txt", productSize);

    if (products == NULL || productSize == 0) {
        cout << "No product available. " << endl;
        return;
    }

    // Hiên thị danh sách sản phẩm
    cout << "Ma san pham\t Ten san pham \t The loai \t Gia \t Hang san xuat \t He dieu hanh \n";
    for (int i = 0; i < productSize; i++) {
        cout << products[i].getProductID() << "\t"
             << products[i].getNameProduct() << "\t"
             << products[i].getGenre() << "\t"
             << products[i].getPriceProduct() << "\t"
             << products[i].getManufacturer() << "\t"
             << products[i].getOperatingSystem() << "\n";
            //  << products[i].getSpecifications() << endl;
    }
    delete [] products;
}