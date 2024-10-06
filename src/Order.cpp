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
    : Products(productID, nameProduct, genre, priceProduct, manufacturer, operatingSystem) // Gọi constructor của lớp cơ sở Products
{
    this->Count = count; // Khởi tạo thuộc tính riêng của Product
}

Order::Order(int productID, string nameProduct, string genre, double priceProduct, string manufacturer, string operatingSystem, int count)
        : Product(productID, nameProduct, genre, priceProduct, manufacturer, operatingSystem, count)
{
    this->count = count;
}
// Products* Order::data = new Products[0]; // khởi tạo mảng động với kích thước ban đầu 

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
        delete[] data; // Giải phóng vùng nhớ cũ
        
        capacity = other.capacity;
        count = other.count;

        data = new Products[capacity]; // Cấp phát lại bộ nhớ
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i]; // Sao chép dữ liệu
        }
    }
    return *this;
}

void Product::loadProducts(const std::string& fileProducts, int& countProducts) {
    std::ifstream file(fileProducts);
    if (!file.is_open()) {
        std::cerr << "Cannot open file!" << std::endl;
        return;
    }
    std::string line;
    while (getline(file, line)) {
        ++countProducts;
    }

    file.clear();
    file.seekg(0, std::ios::beg);
    products = new Products[countProducts];
    int idx = 0;

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string productID, nameProduct, genre, price, manufacturer, operatingSystem, count;
        getline(iss, productID, '|');
        getline(iss, nameProduct, '|');
        getline(iss, genre, '|');
        getline(iss, price, '|');
        getline(iss, manufacturer, '|');
        getline(iss, operatingSystem, '|');
        getline(iss, count);

        try {
            int productsID = std::stoi(productID);               // Chuyển đổi chuỗi thành số nguyên
            double priceProduct = std::stod(price);              // Chuyển đổi chuỗi thành số thập phân
            int counts = std::stoi(count);                       // Chuyển đổi chuỗi thành số nguyên

            products[idx++] = Products(productsID, nameProduct, genre, priceProduct, manufacturer, operatingSystem, counts);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid data in file: " << e.what() << std::endl;
            // Bỏ qua hoặc xử lý sản phẩm có dữ liệu không hợp lệ
        } catch (const std::out_of_range& e) {
            std::cerr << "Number out of range in file: " << e.what() << std::endl;
            // Bỏ qua hoặc xử lý sản phẩm có dữ liệu không hợp lệ
        }
    }
    delete [] products;
}


void Product::displayProduct(){
    if(countProduct == 0){
        loadProducts("D:\\PBL2_GAMESTORE\\text\\Products.txt", countProduct);
    }
    cout << setw(3) << "STT" << setw(10) << "ID" << setw(25) << "Name Product" << setw(15) << "Genre" << setw(25) << "Manufacturer"
        << setw(25) << "Operating System" << setw(10) << "Price" << setw(10) << "Count" << endl;
    for(int i = 0; i < countProduct; i++){
        cout << setw(3) << i + 1
            << setw(10) << products[i].getProductID()
            << setw(25) << products[i].getNameProduct()
            << setw(15) << products[i].getGenre()
            << setw(25) << products[i].getManufacturer()
            << setw(25) << products[i].getOperatingSystem()
            << setw(10) << products[i].getPriceProduct()
            << setw(10) << products[i].getCount() << endl;
    }
}

Products* Order::loadOrder(const string &fileOrder, int &count, int &capacity) {
    ifstream file(fileOrder);
    if (!file.is_open()) {
        cerr << "Cannot open file!" << endl;
        return nullptr;
    }

    Products* product = nullptr;
    string line;
    count = 0;
    capacity = 10;
    bool isOrderStarted = false;
    int k = 0;
    bool customerFound = false;

    // Tìm kiếm khách hàng theo ID
    while (getline(file, line)) {
        if (isOrderStarted && k == 1) {
            k++;
            istringstream iss(line);
            string id;
            getline(iss, id, '|');
            int ID = stoi(id);  // Chuyển chuỗi sang số nguyên
            if (ID == customerID) {
                customerFound = true;
                break;
            }
        }

        if (line == "*") {
            if (!isOrderStarted) {
                // Bắt đầu một Order mới
                isOrderStarted = true;
                k = 1;
            } else {
                isOrderStarted = false;
            }
        }
    }

    // Kiểm tra xem có tìm thấy khách hàng không
    if (!customerFound) {
        cerr << "Customer ID not found!" << endl;
        return nullptr;
    }

    // Nếu tìm thấy khách hàng, khởi tạo mảng product
    product = new Products[capacity];

    // Đọc sản phẩm từ Order
    while (getline(file, line)) {
        if (line == "*") {
            // Kết thúc Order
            file.clear();
            return product;
        }

        // Mở rộng mảng nếu cần
        if (count == capacity) {
            capacity *= 2;
            Products* newProducts = new Products[capacity];
            for (int i = 0; i < count; i++) {
                newProducts[i] = product[i];
            }
            delete[] product;
            product = newProducts;
        }

        // Phân tích dòng thành thông tin sản phẩm
        istringstream iss(line);
        string ID, name, genre, manu, oper, price, n;
        getline(iss, ID, '|');
        getline(iss, name, '|');
        getline(iss, genre, '|');
        getline(iss, price, '|');
        getline(iss, manu, '|');
        getline(iss, oper, '|');
        getline(iss, n);

        try {
            int productsID = std::stoi(ID);               // Chuyển đổi chuỗi thành số nguyên
            double priceProduct = std::stod(price);              // Chuyển đổi chuỗi thành số thập phân
            int counts = std::stoi(n);                       // Chuyển đổi chuỗi thành số nguyên

            products[count] = Products(productsID, name, genre, priceProduct, manu, oper, counts);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid data in file: " << e.what() << std::endl;
            // Bỏ qua hoặc xử lý sản phẩm có dữ liệu không hợp lệ
        } catch (const std::out_of_range& e) {
            std::cerr << "Number out of range in file: " << e.what() << std::endl;
            // Bỏ qua hoặc xử lý sản phẩm có dữ liệu không hợp lệ
        }
    }
    return product;
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
        Order::saveToFile(nameFileOrder);
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
        Order::saveToFile("D:\\PBL2_GAMESTORE\\text\\Orders.txt");
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
    string nameFile = to_string(customerID) + "_order.txt";
    string nameFileOrder = "D:\\PBL2_GAMESTORE\\text\\Order\\" + nameFile;
    int orderSize = 0;
    cout << "Deooo" << " " << customerID << endl;
    Order *orders = FileManager::loadOrder(nameFileOrder, orderSize);
    cout << "Duoccc" << endl;

    if (orders == nullptr || orderSize == 0) {
        cout << "No product available. " << endl;
        return;
    }

    // Hiển thị danh sách sản phẩm trong giỏ hàng
    cout << "Order details:" << endl;
    cout << setw(3) << "STT" << setw(10) << "ID" << setw(25) << "Name Product" << setw(15) << "Genre" << setw(25) << "Manufacturer"
         << setw(25) << "Operating System" << setw(10) << "Price" << setw(10) << "Count" << endl;

    double sum = 0;
    for (int i = 0; i < orderSize; i++) {
        sum += orders[i].getCount() * orders[i].getPriceProduct();
        cout << setw(3) << i + 1
             << setw(10) << orders[i].getProductID()
             << setw(25) << orders[i].getNameProduct()
             << setw(15) << orders[i].getGenre()
             << setw(25) << orders[i].getManufacturer()
             << setw(25) << orders[i].getOperatingSystem()
             << setw(10) << orders[i].getPriceProduct()
             << setw(10) << orders[i].getCount() << endl;
    }
    cout << "Total Price: " << sum << endl;

    // Giải phóng bộ nhớ
    delete[] orders; 
}


// void Order::saveToFile(const string& filename) const{
//     ofstream outFile(filename, ios::app);
//     if (outFile.is_open()) {
//         outFile << "*" << endl;
//         outFile << customerID << endl;
//         outFile << "Order Details: " << endl;
//         for (int i = 0; i < count; i++) {
//             // outFile << i + 1
//             outFile << data[i].getProductID() << "|"
//                     << data[i].getNameProduct() << "|"
//                     << data[i].getGenre() << "|"
//                     << data[i].getPriceProduct() << "|"
//                     << data[i].getManufacturer() << "|"
//                     << data[i].getOperatingSystem() << "|"
//                     << data[i].getCount() << endl;
//         }
//         outFile << "*" << endl;
//         outFile.close();
//     }
//     else {
//         cout << "Unable to open file " << filename << endl;
//     }
// }

void Order::saveToFile(const string& filename) const{
    ofstream outFile(filename);
    if (outFile.is_open()) {
        // outFile << customerID << "|";
        for (int i = 0; i < count; i++) {
            // outFile << i + 1
            outFile << data[i].getProductID() << "|"
                    << data[i].getNameProduct() << "|"
                    << data[i].getGenre() << "|"
                    << data[i].getPriceProduct() << "|"
                    << data[i].getManufacturer() << "|"
                    << data[i].getOperatingSystem() << "|"
                    << data[i].getCount() << endl;
        }
        outFile.close();
    }
    else {
        cout << "Unable to open file " << filename << endl;
    }
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

void Order::saveToFile(const string& filename, int stt) const{
    ofstream outFile(filename, ios::app);
    if (outFile.is_open()) {
        outFile << "*" << endl;
        outFile << customerID << endl;
        outFile << "Order details:" << endl;
        outFile << data[stt].getProductID() << "|"
            << data[stt].getNameProduct() << "|"
            << data[stt].getGenre() << "|"
            << data[stt].getPriceProduct() << "|"
            << data[stt].getManufacturer() << "|"
            << data[stt].getOperatingSystem() << "|"
            << data[stt].getCount() << endl;
        outFile << "*" << endl;
        outFile.close();
    }
    else {
        cout << "Unable to open file " << filename << endl;
    }
}

void Product::saveToFile(const string fileProducts){
    ofstream outFile(fileProducts, ios::out);
    if (outFile.is_open()) {
        for(int i = 0; i < countProduct; i++){
            outFile << products[i].getProductID() << "|"
                << products[i].getNameProduct() << "|"
                << products[i].getGenre() << "|"
                << products[i].getPriceProduct() << "|"
                << products[i].getManufacturer() << "|"
                << products[i].getOperatingSystem() << "|"
                << products[i].getCount() << endl;
        }
        outFile.close();
    }
    else {
        cout << "Unable to open file " << fileProducts << endl;
    }
}

void Order::change(int stt){
    int k;
    for(int i = 0; i < countProduct; i++){
        if(products[i].getProductID() == Order::data[stt].getProductID()){
            k = products[i].getCount() - data[stt].getCount();
            if(k >= 0){
                products[i].setCount(k);
                count --;
                for(int j = stt; j < count; j++){
                    data[j] = data[j+1];
                }
            }
            else{
                cout << "Sorry, the product is out of stock." << endl;
            }
        }
    }
}

void Order::change(){
    for(int i = 0; i < count; i++){
        change(i);
    }
}
 


void Order::pay(){
    cout << "1. Pay for a product" << endl;
    cout << "2. Pay for all products in cart" << endl;
    cout << "0. Exit" << endl;
    int n, stt;
    cout << "Enter choice: ";
    cin >> n;
    switch (n){
        case 1:{
            cout << "Enter choice(STT): ";
            cin >> stt;
            Order::saveToFile("D:\\PBL2_GAMESTORE\\text\\Pay.txt", stt - 1);
            change(stt - 1);
            Product::saveToFile("D:\\PBL2_GAMESTORE\\text\\Products.txt");
            break;
        }
        case 2:{
            Order::saveToFile("D:\\PBL2_GAMESTORE\\text\\Pay.txt");
            change();
            Product::saveToFile("D:\\PBL2_GAMESTORE\\text\\Products.txt");
            break;
        }
        default:
            return;
    }
}