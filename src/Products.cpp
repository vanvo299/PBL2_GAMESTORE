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

void Products::displayProducts()
{
    int productSize;
    Products *products = FileManager::loadProducts("D:\\PBL2_GAMESTORE\\text\\Products.txt", productSize);

    if (products == NULL || productSize == 0) {
        cout << "No product available. " << endl;
        return;
    }

    // Hiên thị danh sách sản phẩm
    cout << setw(3) << "STT" << setw(10) << "ID" << setw(25) << "Name Product" << setw(15) << "Genre" << setw(25) << "Manufacturer"
        << setw(25) << "Operating System" << setw(10) << "Price" << setw(7) << "Count" << endl;
    for (int i = 0; i < productSize; i++) {
        cout << setw(3) << i + 1
            << setw(10) << products[i].productID
            << setw(25) << products[i].nameProduct
            << setw(15) << products[i].genre
            << setw(25) << products[i].manufacturer
            << setw(25) << products[i].operatingSystem
            << setw(10) << products[i].priceProduct 
            << setw(7) << products[i].Count << endl;
    }
    delete [] products;
}