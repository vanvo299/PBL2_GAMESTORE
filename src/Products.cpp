#include "D:\PBL2_GAMESTORE\include\Products.h"
#include "D:\PBL2_GAMESTORE\include\FileManager.h"
#include <iomanip>

Products::Products(int productID, string nameProduct, string genre, double priceProduct, string manufacturer, string operatingSystem, int Count){
    this->productID = productID;
    this->nameProduct = nameProduct;
    this->genre = genre;
    this->priceProduct = priceProduct;
    this->manufacturer = manufacturer;
    this->operatingSystem = operatingSystem;
    this->Count = Count;
}
Products::Products(int productID, string specifications)
{
    this->productID = productID;
    this->specifications = specifications;
}
Products::Products(int productID, string nameProduct, string genre, double priceProduct, string manufacturer, string operatingSystem, string specifications, int Count){
    this->productID = productID;
    this->nameProduct = nameProduct;
    this->genre = genre;
    this->priceProduct = priceProduct;
    this->manufacturer = manufacturer;
    this->operatingSystem = operatingSystem;
    this->specifications = specifications;
    this->Count = Count;
}

Products::Products(){}
Products::~Products(){}


// getter
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


// setting
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

    cout << setw(3) << "STT" << setw(10) << "ID" << setw(25) << "Name Product" << setw(15) << "Genre" << setw(25) << "Manufacturer"
        << setw(25) << "Operating System" << setw(10) << "Price" << setw(10) << "Count" << endl;
    for(int i = 0; i < productSize; i++){
        cout << setw(3) << i + 1
            << setw(10) << products[i].getProductID()
            << setw(25) << products[i].getNameProduct()
            << setw(15) << products[i].getGenre()
            << setw(25) << products[i].getManufacturer()
            << setw(25) << products[i].getOperatingSystem()
            << setw(10) << products[i].getPriceProduct()
            << setw(10) << products[i].getCount() << endl;
    }
    delete [] products;
}

void Products::displaySpecification(int productID)
{
    bool check = false;
    int productSize;
    Products *products = FileManager::loadSpecifications("D:\\PBL2_GAMESTORE\\text\\ThongSoKyThuat.txt", productSize);

    if (products == NULL || productSize == 0) {
        cout << "No product available. \n";
        return;
    }
    for (int i = 0; i < productSize; i++) {
        if (products[i].getProductID() == productID) {
            cout << "Thong so ky thuat \n";
            cout << products[i].getSpecifications() << endl;
            check = true;
        } 
    }
    if (!check)
        cout << "Products not found ! \n";
    delete [] products;
}