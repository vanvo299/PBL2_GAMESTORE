#include "D:\PBL2_GAMESTORE\include\Products.h"
#include "D:\PBL2_GAMESTORE\include\FileManager.h"

Products::Products(int productID, string nameProduct, string genre, double priceProduct, string manufacturer, string operatingSystem, string specifications)
{
    this->productID = productID;
    this->nameProduct = nameProduct;
    this->genre = genre;
    this->priceProduct = priceProduct;
    this->manufacturer = manufacturer;
    this->operatingSystem = operatingSystem;
    this->specifications = specifications;
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

int Products::getProductID()
{
    return productID;
}

string Products::getNameProduct()
{
    return nameProduct;
}

string Products::getGenre()
{
    return genre;
}

double Products::getPriceProduct()
{
    return priceProduct;
}


string Products::getManufacturer()
{
    return manufacturer;
}

string Products::getOperatingSystem()
{
    return operatingSystem;
}

string Products::getSpecifications()
{
    return specifications;
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
        cout << setw(3) << "STT" << setw(10) << "ID" << setw(25) << "Name Product" << setw(15) << "Genre" << setw(25) << "Price Product"
        << setw(25) << "Manufacturer" << setw(10) << "Operating System" << setw(10) << endl;
    for (int i = 0; i < productSize; i++) {
        cout << setw(3) << i + 1
            << setw(10) << products[i].productID
            << setw(25) << products[i].nameProduct
            << setw(15) << products[i].genre
            << setw(10) << products[i].priceProduct
            << setw(25) << products[i].manufacturer
            << setw(25) << products[i].operatingSystem << endl;
    }

}
// Hiển thị thông tin thông số kĩ thuật của sản phẩm
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