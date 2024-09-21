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