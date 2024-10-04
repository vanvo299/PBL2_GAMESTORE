#include "D:\PBL2_GAMESTORE\include\Admin.h"

Admin::Admin() {};
Admin::~Admin() {};

// Thêm sản phẩm
void Admin::addProduct()
{
    int productID;
    string nameProduct, genre, manufacturer, operatingSystem, specifications;
    double priceProduct;

    string fileName, line;
    cout << "Enter specification file name (without path): ";
    cin >> fileName;

    string fileProduct = "D:\\PBL2_GAMESTORE\\text\\ThietBi\\" + fileName;

    cout << "Enter product ID: ";
    cin >> productID;
    // Kiểm tra xem productID đã tồn tại chưa
    ifstream checkFile("D:\\PBL2_GAMESTORE\\text\\Products.txt");
    bool idExists = false;
    while (getline(checkFile, line)) {
        if (line.find(to_string(productID) + "|") != string::npos) {
            idExists = true;
            break;
        }
    }
    checkFile.close();

    if (idExists) {
        cout << "Product ID already exists. Please enter a unique ID.\n";
        return;
    }

    cin.ignore();
    cout << "Enter name product: ";
    getline(cin, nameProduct);
    cout << "Enter genre: ";
    getline(cin, genre);
    cout << "Enter price product: ";
    cin >> priceProduct;
    cin.ignore();
    cout << "Enter manufacturer: ";
    getline(cin, manufacturer);
    cout << "Enter operating system: ";
    getline(cin, operatingSystem);

    // Mở file để lưu sản phẩm mới
    ofstream outFile("D:\\PBL2_GAMESTORE\\text\\Products.txt", ios::app);

    if (outFile.is_open()) {
        // Ghi thông tin sản phẩm vào file
        outFile << productID << '|' <<
                   nameProduct << '|' <<
                   genre << '|' <<
                   priceProduct << '|' <<
                   manufacturer << '|' <<
                   operatingSystem << endl;
        outFile.close();
    }

    // Ghi chi tiết thông số kĩ thuật vào file
    ifstream inFile(fileProduct);
    ofstream saveSpecification("D:\\PBL2_GAMESTORE\\text\\ThongSoKyThuat.txt", ios::app);

    if (!inFile.is_open() || !saveSpecification.is_open()) {
        cout << "Cann't open file. \n";
        return;
    }


    saveSpecification << endl << "*" << endl;
    saveSpecification << productID << '|' << endl;
    while(getline(inFile, line)) {
        saveSpecification << line << endl;
    }
    saveSpecification << "*" << endl;

    inFile.close();
    saveSpecification.close();

    cout << "Product " << nameProduct <<  " has been added successfully. \n";
}

// Xóa sản phẩm (1/2)
void Admin::deleteProduct() {
    int productID;
    cout << "Enter product ID to delete: ";
    cin >> productID;

    // Mở file để đọc thông số kỹ thuật
    ifstream inFile_specification("D:\\PBL2_GAMESTORE\\text\\ThongSoKyThuat.txt");
    if (!inFile_specification.is_open()) {
        cout << "Error: Can't open specification file.\n";
        return;
    }

    string content, line;
    bool isInsideProduct = false; // Biến đánh dấu đã vào một sản phẩm
    bool removeProduct = false; // Biến để đánh dấu sản phẩm cần xóa

    while (getline(inFile_specification, line)) {
        if (line == "*") {
            if (isInsideProduct) {
                if (removeProduct) {
                    // Nếu đang ở cuối sản phẩm cần xóa
                    isInsideProduct = false; // Kết thúc sản phẩm
                    removeProduct = false; // Đặt lại biến
                    continue; // Bỏ qua dấu *
                } else {
                    // Nếu không phải sản phẩm cần xóa, giữ nguyên dấu *
                    content += line + "\n";
                    isInsideProduct = false; // Kết thúc sản phẩm
                }
            } else {
                // Bắt đầu một sản phẩm mới
                isInsideProduct = true;
            }
            continue; // Bỏ qua dấu *
        }

        // Kiểm tra xem dòng hiện tại có chứa productID không
        if (isInsideProduct && line.find(std::to_string(productID) + "|") != string::npos) {
            removeProduct = true; // Đã tìm thấy sản phẩm cần xóa
            continue; // Bỏ qua sản phẩm cần xóa
        }

        // Nếu không xóa, thêm dòng vào nội dung
        if (!removeProduct) {
            content += line + "\n"; // Ghi lại nội dung
        }
    }
    inFile_specification.close();

    // Ghi lại nội dung đã cập nhật vào file
    ofstream outFile_specification("D:\\PBL2_GAMESTORE\\text\\ThongSoKyThuat.txt");
    if (!outFile_specification.is_open()) {
        cout << "Error: Can't open specification file to write.\n";
        return;
    }
    outFile_specification << content;
    outFile_specification.close();

    // Xóa trong file Products
    ifstream inFile("D:\\PBL2_GAMESTORE\\text\\Products.txt");
    if (!inFile.is_open()) {
        cout << "Error: Can't open product file.\n";
        return;
    }

    Products* product = nullptr;
    int countProduct = 0;

    // Đếm số lượng sản phẩm
    while (getline(inFile, line)) {
        ++countProduct;
    }

    inFile.clear();
    inFile.seekg(0, ios::beg);

    product = new Products[countProduct];
    int index = 0;
    bool productFound = false;

    while (getline(inFile, line)) {
        // Đọc toàn bộ file và lưu vào mảng động, trừ sản phẩm có ID cần xóa
        if (line.find(std::to_string(productID) + "|") != string::npos) {
            productFound = true;
            continue; // Bỏ qua sản phẩm cần xóa
        }

        istringstream iss(line);
        string productID_str, nameProduct, genre, priceProduct_str, manufacturer, operatingSystem;
        getline(iss, productID_str, '|');
        getline(iss, nameProduct, '|');
        getline(iss, genre, '|');
        getline(iss, priceProduct_str, '|');
        getline(iss, manufacturer, '|');
        getline(iss, operatingSystem, '|');

        int id = stoi(productID_str);
        double priceProduct = stod(priceProduct_str);

        product[index++] = Products(id, nameProduct, genre, priceProduct, manufacturer, operatingSystem);
    }

    // Ghi lại các sản phẩm vào file (đã xóa sản phẩm cần xóa)
    ofstream outFile("D:\\PBL2_GAMESTORE\\text\\Products.txt");
    if (!outFile.is_open()) {
        cout << "Error: Can't open product file to write.\n";
        delete[] product; // Giải phóng bộ nhớ trước khi kết thúc
        return;
    }

    for (int i = 0; i < index; i++) {
        outFile << product[i] << endl; // Định nghĩa toán tử << cho Products
    }

    outFile.close();
    inFile.close();
    delete[] product; // Giải phóng bộ nhớ

    if (productFound) {
        cout << "Product with ID " << productID << " deleted successfully.\n";
    } else {
        cout << "Product with ID " << productID << " not found.\n";
    }
}

// Sửa thông tin sản phẩm
void Admin::editProduct()
{
    int productID;
    cout << "Enter the product ID to edit: ";
    cin >> productID;

    int productSize;
    Products *product = FileManager::loadProducts("D:\\PBL2_GAMESTORE\\text\\Products.txt", productSize);

    if (product == NULL || productSize == 0) {
        cout << "No product available. \n";
        return;
    }

    bool productFound = false;

    for (int i = 0; i < productSize; i++) {
        if (productID == product[i].getProductID()) {
            string newNameProduct, newGenre, newManufacturer, newOperatingSystem;
            double newPriceProduct;
            cin.ignore();
            cout << "Enter name product: ";
            getline(cin, newNameProduct);
            cout << "Enter genre: ";
            getline(cin, newGenre);
            cout << "Enter price product: ";
            cin >> newPriceProduct;
            cin.ignore();
            cout << "Enter manufacturer: ";
            getline(cin, newManufacturer);
            cout << "Enter operating system: ";
            getline(cin, newOperatingSystem);

            // Đọc file và cập nhật thông tin sản phẩm
            ifstream inFile("D:\\PBL2_GAMESTORE\\text\\Products.txt");
            if (!inFile.is_open()){
                cout << "Unable to open file for reading. \n";
                delete [] product;
                return;
            }

            string line, fileContent;
            
            // Đọc từng dòng và xử lí
            while(getline(inFile, line)) {
                istringstream iss(line);
                string id, nameProduct, genre, priceProduct_str, manufacturer, operatingSystem;
                // Phân tách dòng hiện tại bằng dấu phân cách |
                getline(iss, id, '|');
                getline(iss, nameProduct, '|');
                getline(iss, genre, '|');
                getline(iss, priceProduct_str, '|');
                getline(iss, manufacturer, '|');
                getline(iss, operatingSystem);


                // Cập nhật nếu đúng sản phẩm
                if (stoi(id) == productID) {
                    nameProduct = newNameProduct;
                    genre = newGenre;
                    priceProduct_str = to_string(newPriceProduct);  // Cập nhật giá trị mới
                    manufacturer = newManufacturer;
                    operatingSystem = newOperatingSystem;
                }


                fileContent += id + '|' + nameProduct + '|' + genre + '|' + priceProduct_str + '|' + manufacturer + '|' + operatingSystem + "\n";
            }
            inFile.close();

            ofstream outFile("D:\\PBL2_GAMESTORE\\text\\Products.txt", ios::trunc);
            if (!outFile.is_open()) {
                cout << "Unable to open file for writing. \n";
                delete [] product;
                return;
            }

            outFile << fileContent;
            outFile.close();
            cout << "Update information product successfully. \n";
            productFound = true;
            break;
        } 
    }
    if (!productFound) {
        cout << "No product found with the given ID. \n";
    }

    delete [] product;
}