#include "D:\PBL2_GAMESTORE\include\Order.h"
#include "D:\PBL2_GAMESTORE\include\Products.h"
#include "D:\PBL2_GAMESTORE\include\Customer.h"
#include "D:\PBL2_GAMESTORE\include\FileManager.h"

using namespace std;

int Product::countProduct = 0;

Products* Product::products = new Products[0];


Product::Product(){}

Product::Product(int n){
    this->countProduct = n;
    products = new Products [n];
}

Product::~Product(){
    delete [] products;
}

Product& Product::operator = (const Product& other){
    if (this != &other) { // Kiểm tra tự gán
        delete[] products; // Giải phóng vùng nhớ cũ
        countProduct = other.countProduct;
        products = new Product[countProduct]; // Cấp phát lại bộ nhớ
        for (int i = 0; i < countProduct; i++) {
            products[i] = other.products[i]; // Sao chép dữ liệu
        }
    }
    return *this;
}

int Product::getCountP(){
    return countProduct;
}

int Order::customerID = 0;

void Order::setID(int ID){
    this->customerID = ID;
}

// Định nghĩa constructor cho lớp Product
Product::Product(int productID, string nameProduct, string genre, double priceProduct, string manufacturer, string operatingSystem, int count)
    : Products(productID, nameProduct, genre, priceProduct, manufacturer, operatingSystem, count) // Gọi constructor của lớp cơ sở Products
{
    this->Count = count; // Khởi tạo thuộc tính riêng của Product
}

Order::Order(int capacity){
    this->count = 0;
    this->capacity = capacity;
    data = new Products[capacity];
}

Order::Order(const Order& other) {
    this->capacity = other.capacity;
    this->count = other.count;
    data = new Products[capacity]; // Tạo mảng mới
    for (int i = 0; i < count; i++) {
        data[i] = other.data[i]; // Sao chép từng phần tử
    }
}

Order::~Order() {
    delete[] data; // phải phóng bộ nhớ
}

Order& Order::operator = (const Order& other) {
    if (this != &other) { // Kiểm tra tự gán        
        capacity = other.capacity;
        count = other.count;

        data = new Products[capacity]; // Cấp phát lại bộ nhớ
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i]; // Sao chép dữ liệu
        }
    }
    return *this;
}
void Order::update(){
    string nameFile = to_string(customerID) + "_order.txt";
    string nameFileOrder = "D:\\PBL2_GAMESTORE\\text\\Order\\" + nameFile;
    data = FileManager::loadOrder(nameFileOrder, count, capacity);
}

void Product::displayProduct(){
    if(countProduct == 0){
        products = FileManager::loadProducts("D:\\PBL2_GAMESTORE\\text\\Products.txt", countProduct);
    }
    cout << setw(3) << "STT" << setw(13) << "ID" << setw(30) << "Name Product" << setw(15) << "Genre" << setw(25) << "Manufacturer"
         << setw(25) << "Operating System" << setw(10) << "Price" << setw(10) << "Count" << endl;
    for(int i = 0; i < countProduct; i++){
        cout << setw(3) << i + 1
            << setw(13) << products[i].getProductID()
            << setw(30) << products[i].getNameProduct()
            << setw(15) << products[i].getGenre()
            << setw(25) << products[i].getManufacturer()
            << setw(25) << products[i].getOperatingSystem()
            << setw(10) << products[i].getPriceProduct()
            << setw(10) << products[i].getCount() << endl;
    }
}

void Order::addData(int ID) {
    if (count == capacity) {
        increaseCapacity();
    }
    int found = 1;
    for (int i = 0; i < countProduct; i++) {
        if (products[i].getProductID() == ID) {
            for (int j = 0; j < count; j++) {
                if (data[j].getProductID() == ID) {
                    data[j].setCount(data[j].getCount() + 1);
                    found = 2;
                }
            }
            if(found == 1){
                data[count].setProductID(products[i].getProductID());
                data[count].setNameProduct(products[i].getNameProduct());
                data[count].setGenre(products[i].getGenre());
                data[count].setManufacturer(products[i].getManufacturer());
                data[count].setOperatingSystem(products[i].getOperatingSystem());
                data[count].setPriceProduct(products[i].getPriceProduct());
                data[count].setCount(1);
                count++;
                found = 3;
            }
        }
    }
    if(found == 2 || found == 3){
        string nameFile = to_string(customerID) + "_order.txt";
        string nameFileOrder = "D:\\PBL2_GAMESTORE\\text\\Order\\" + nameFile;
        FileManager::saveOrder(nameFileOrder,data, count);
    }
}


void Order::addData(string name) {
    if (count == capacity) {
        increaseCapacity();
    }
    int found = 1;
    for (int i = 0; i < countProduct; i++) {
        if (products[i].getNameProduct() == name) {
            for (int j = 0; j < count; j++) {
                if (data[j].getNameProduct() == name) {
                    data[j].setCount(data[j].getCount() + 1);
                    found = 2;
                }
            }
            if(found == 1){
                data[count].setProductID(products[i].getProductID());
                data[count].setNameProduct(products[i].getNameProduct());
                data[count].setGenre(products[i].getGenre());
                data[count].setManufacturer(products[i].getManufacturer());
                data[count].setOperatingSystem(products[i].getOperatingSystem());
                data[count].setPriceProduct(products[i].getPriceProduct());
                data[count].setCount(1);
                count++;
                found = 3;
            }
        }
    }
    if(found == 2 || found == 3) {
        string nameFile = to_string(customerID) + "_order.txt";
        string nameFileOrder = "D:\\PBL2_GAMESTORE\\text\\Order\\" + nameFile;
        FileManager::saveOrder(nameFileOrder,data, count);
    }
}

void Order::deleteData(int ID) {
    bool found = false;
    for (int i = 0; i < countProduct; i++) {
        if (data[i].getProductID() == ID) {
            for (int j = i; j < count - 1; j++) {
                data[j] = data[j + 1];
            }
            count--;
            found = true;
            products[i].setCount(products[i].getCount() + 1);
            string nameFile = to_string(customerID) + "_order.txt";
            string nameFileOrder = "D:\\PBL2_GAMESTORE\\text\\Order\\" + nameFile;
            FileManager::saveOrder(nameFileOrder,data, count);
            break;
        }
    }
    if (!found) {
        cout << "Not found in order" << endl;
    }
}

void Order::deleteData(string name) {
    bool found = false;
    for (int i = 0; i < countProduct; i++) {
        if (data[i].getNameProduct() == name) {
            for (int j = i; j < count - 1; j++) {
                data[j] = data[j + 1];
            }
            count--;
            found = true;
            products[i].setCount(products[i].getCount() + 1);
            string nameFile = to_string(customerID) + "_order.txt";
            string nameFileOrder = "D:\\PBL2_GAMESTORE\\text\\Order\\" + nameFile;
            FileManager::saveOrder(nameFileOrder,data, count);
            break;
        }
    }
    if (!found) {
        cout << "Not found in order" << endl;
    }
}

void Order::increaseCapacity() {
    capacity = capacity * 2;
    Products* newdata = new Products[capacity];

    //sao chep mảng củ sang mảng mới
    for (int i = 0; i < count; i++) {
        newdata[i] = data[i];
    }
    delete[] data;
    data = newdata;
}

void Order::displayOrder() 
{
    cout << "Deooo" << " " << customerID << endl;
    cout << "Duoccc" << endl;

    // Hiển thị danh sách sản phẩm trong giỏ hàng
    cout << "Order details:" << endl;
    cout << setw(3) << "STT" << setw(13) << "ID" << setw(30) << "Name Product" << setw(15) << "Genre" << setw(25) << "Manufacturer"
         << setw(25) << "Operating System" << setw(10) << "Price" << setw(10) << "Count" << endl;

    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += data[i].getCount() * data[i].getPriceProduct();
        cout << setw(3) << i + 1
             << setw(13) << data[i].getProductID()
             << setw(30) << data[i].getNameProduct()
             << setw(15) << data[i].getGenre()
             << setw(25) << data[i].getManufacturer()
             << setw(25) << data[i].getOperatingSystem()
             << setw(10) << data[i].getPriceProduct()
             << setw(10) << data[i].getCount() << endl;
    }
    cout << "Total Price: " << sum << endl;
}

int Order::findData(int& ID) const {
    for (int i = 0; i < count; i++) {
        if (data[i].getProductID() == ID) {
            return i; // Trả về vị trí của mặt hàng
        }
    }
    return -1; // Không tìm thấy
}

int Order::findData(const string& name) const {
    for (int i = 0; i < count; i++) {
        if (data[i].getNameProduct() == name) {
            return i; // Trả về vị trí của mặt hàng
        }
    }
    return -1; // Không tìm thấy
}

void Order::updateData(int& ID, const string& name, const string& genre, const string& manu, const string& oper, double newPrice, int count) {
    int index = findData(ID);
    if (index != -1) {
        data[index].setProductID(ID);
        data[index].setNameProduct(name);
        data[index].setGenre(genre);
        data[index].setPriceProduct(newPrice);
        data[index].setManufacturer(manu);
        data[index].setOperatingSystem(oper);
        data[index].setCount(count);
    }
    else {
        cout << "Item not found!" << endl;
    }
}

void Order::clearOrder() {
    if (data != nullptr) {  // Kiểm tra NULL trước khi xóa
        delete[] data; // giải phóng bộ nhớ củ
    }
    data = new Products[capacity]; // Khởi tạo lại mảng mới
    count = 0;
}

void Order::sortOrderByPrice() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (data[i].getProductID() > data[j].getProductID()) {
                swap(data[i], data[j]); // Đổi chỗ nếu giá lớn hơn
            }
        }
    }
}

void Order::change(){
    int k;
    Products *arr = new Products [capacity];
    Products* pay = new Products [capacity];
    int n = 0, h = 0;
    for(int i = 0; i < countProduct; i++){
        for(int j = 0; j < count; j++){
            if(products[j].getProductID() == Order::data[i].getProductID()){
                k = products[j].getCount() - data[i].getCount();
                if(k >= 0){
                    products[j].setCount(k);
                    pay[h++] = data[i];
                }
                else{
                    arr[n++] = data[i];
                    cout << "Sorry, the product: " << products[j].getNameProduct() << " is out of stock." << endl;
                }
            }
        }
    }
    FileManager::savePay("D:\\PBL2_GAMESTORE\\text\\Pay.txt", pay, h, customerID);
    FileManager::saveProducts("D:\\PBL2_GAMESTORE\\text\\Products.txt", products, countProduct);
    delete [] pay;
    delete [] data;
    data = arr;
    string nameFile = to_string(customerID) + "_order.txt";
    string nameFileOrder = "D:\\PBL2_GAMESTORE\\text\\Order\\" + nameFile;
    count = n;
    FileManager::saveOrder(nameFileOrder,data, count);
    delete [] arr;
}

void Order::pay(){
    cout << "1. Delete a product in cart" << endl;
    cout << "2. Pay for all products in cart" << endl;
    cout << "0. Exit" << endl;
    int n, IDproduct;
    cout << "Enter choice: ";
    cin >> n;
    switch (n){
        case 1:{
            cout << "Enter choice(product ID): ";
            cin >> IDproduct;
            deleteData(IDproduct);
            break;
        }
        case 2:{
            change();
            break;
        }
        default:
            return;
    }
}
