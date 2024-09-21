
#include "D:\PBL2_GAMESTORE\include\Order.h"
#include "D:\PBL2_GAMESTORE\include\Customer.h"

using namespace std;

Order::Order(int cap) : capacity(cap), count(0), totalPrice(0.0) {
    data = new Data[capacity]; // khởi tạo mảng động với kích thước ban đầu
}

Order::Order(const Order& other) : capacity(other.capacity), count(other.count), totalPrice(other.totalPrice) {
    data = new Data[capacity]; // Tạo mảng mới
    for (int i = 0; i < count; i++) {
        data[i] = other.data[i]; // Sao chép từng phần tử
    }
}

Order::~Order() {
    delete[] data; // phải phóng bộ nhớ
}

Order& Order::operator = (const Order& other) {
    if (this != &other) { // Kiểm tra tự gán
        delete[] data; // Giải phóng vùng nhớ cũ
        
        capacity = other.capacity;
        count = other.count;
        totalPrice = other.totalPrice;

        data = new Data[capacity]; // Cấp phát lại bộ nhớ
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i]; // Sao chép dữ liệu
        }
    }
    return *this;
}


void Order::addData(int ID, const string& name, const string& gen, const string& manu, const string& oper, double price, int n) {
    if (count == capacity) {
        increaseCapacity();
    }
    data[count].productID = ID;
    data[count].nameProduct = name;
    data[count].genre = gen;
    data[count].manufacturer = manu;
    data[count].operatingSystem = oper;
    data[count].priceProduct = price;
    data[count].amount = n;
    count++;
    totalPrice += n * price;
    Order::saveToFile("D:\\PBL2_GAMESTORE\\text\\Orders.txt");
}

void Order::deleteData(int ID) {
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (data[i].productID == ID) {
            totalPrice -= data[i].amount * data[i].priceProduct;
            for (int j = i; j < count - 1; j++) {
                data[j] = data[j + 1];
            }
            count--;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Not found in order" << endl;
    }
}

void Order::increaseCapacity() {
    capacity = capacity * 2;
    Data* newdata = new Data[capacity];

    //sao chep mảng củ sang mảng mới
    for (int i = 0; i < count; i++) {
        newdata[i] = data[i];
    }
    delete[] data;
    data = newdata;
}

void Order::displayOrder() const {
    cout << "Order details:" << endl;
    cout << setw(3) << "STT" << setw(10) << "ID" << setw(25) << "Name Product" << setw(15) << "Genre" << setw(25) << "Manufacturer"
        << setw(25) << "Operating System" << setw(10) << "Price" << setw(10) << "Count" << endl;
    for (int i = 0; i < count; i++) {
        cout << setw(3) << i + 1
            << setw(10) << data[i].productID
            << setw(25) << data[i].nameProduct
            << setw(15) << data[i].genre
            << setw(25) << data[i].manufacturer
            << setw(25) << data[i].operatingSystem
            << setw(10) << data[i].priceProduct
            << setw(10) << data[i].amount << endl;
    }
    cout << "Total Price: " << totalPrice << endl;
}

void Order::saveToFile(const string& filename) const{
    ofstream outFile(filename, ios::app);
    if (outFile.is_open()) {
        outFile << "*" << endl;
        outFile << "Order details:" << endl;
        for (int i = 0; i < count; i++) {
            // outFile << i + 1
            outFile << data[i].productID << "|"
                    << data[i].nameProduct << "|"
                    << data[i].genre << "|"
                    << data[i].manufacturer << "|"
                    << data[i].operatingSystem << "|"
                    << data[i].priceProduct << "|"
                    << data[i].amount << endl;
        }
        outFile << "Total Price: $" << totalPrice << endl;
        outFile << "*" << endl;
        outFile.close();
    }
    else {
        cout << "Unable to open file " << filename << endl;
    }
}

int Order::findData(int& ID) const {
    for (int i = 0; i < count; i++) {
        if (data[i].productID == ID) {
            return i; // Trả về vị trí của mặt hàng
        }
    }
    return -1; // Không tìm thấy
}

int Order::findData(const string& name) const {
    for (int i = 0; i < count; i++) {
        if (data[i].nameProduct == name) {
            return i; // Trả về vị trí của mặt hàng
        }
    }
    return -1; // Không tìm thấy
}

void Order::updateData(int& ID, const string& name, const string& gen, const string& manu, const string& oper, double newPrice) {
    int index = findData(ID);
    if (index != -1) {
        totalPrice -= data[index].amount * data[index].priceProduct; // Trừ giá trị cũ
        data[index].nameProduct = name;
        data[index].genre = gen;
        data[index].manufacturer = manu;
        data[index].operatingSystem = oper;
        data[index].priceProduct = newPrice;
        totalPrice += data[index].amount * newPrice; // Cộng giá trị mới
    }
    else {
        cout << "Item not found!" << endl;
    }
}

void Order::clearOrder() {
    if (data != nullptr) {  // Kiểm tra NULL trước khi xóa
        delete[] data; // giải phóng bộ nhớ củ
    }
    data = new Data[capacity]; // Khởi tạo lại mảng mới
    count = 0;
    totalPrice = 0.0;
}

void Order::sortOrderByPrice() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (data[i].priceProduct > data[j].priceProduct) {
                swap(data[i], data[j]); // Đổi chỗ nếu giá lớn hơn
            }
        }
    }
}

