#include "D:\PBL2_GAMESTORE\include\FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Hàm nạp danh sách game từ file vào mảng
Customer* FileManager::loadCustomer(const std::string& fileCustomer, int &countCustomer)
{
    std::ifstream file(fileCustomer);
    Customer* customers = NULL;
    countCustomer = 0;

    if (file.is_open()) {
        std::string line;
        // Đếm số lượng khách hàng
        while(getline(file, line)) {
            ++countCustomer;
        }

        // Đếm xong và quay lại đầu file và cấp phát mảng và ghi dữ liệu vào mảng
        file.clear();
        file.seekg(0, std::ios::beg); // seekg dùng để di chuyển con trỏ về vị trí 0 đầu file
        customers = new Customer[countCustomer];
        int idx = 0;

        while(getline(file, line)) {
            std::istringstream iss(line);
            std::string customerID_str, customerName, email, phone, userName, password;

            // Tách các thành phần trong dòng bằng dấu |
            std::getline(iss, customerID_str, '|');
            std::getline(iss, customerName, '|');
            std::getline(iss, email, '|');
            std::getline(iss, phone, '|');
            std::getline(iss, userName, '|');
            std::getline(iss, password, '|');

            // Chuyển ID từ chuỗi thành số nguyên
            int customerID = std::stoi(customerID_str);

            // Tạo Customer và lưu vào mảng
            customers[idx++] = Customer(customerID, customerName, email, phone, userName, password);
        }
    }
    return customers;
}

Game* FileManager::loadGames(const std::string &fileGame, int &countGame)
{
    std::ifstream file(fileGame);
    Game *games = NULL;
    countGame = 0;

    if (file.is_open()) {
        std::string line;
        // Đếm số lượng khách hàng
        while(getline(file, line)) {
            ++countGame;
        }

        // Đếm xong và quay lại đầu file và cấp phát mảng và ghi dữ liệu vào mảng
        file.clear();
        file.seekg(0, std::ios::beg);
        games = new Game[countGame];
        int idx = 0;

        while(getline(file, line)) {
            std::istringstream iss(line);
            std::string gameID_str, nameGame, genre, priceGame_str, gamesInStock_str;

            // Tách các thành phần trong dòng bởi dấu |
            std::getline(iss, gameID_str, '|');
            std::getline(iss, nameGame, '|');
            std::getline(iss, genre, '|');
            std::getline(iss, priceGame_str, '|');
            std::getline(iss, gamesInStock_str, '|');

            // Chuyển ID từ chuỗi thành số nguyên
            int idGame = std::stoi(gameID_str);
            double priceGame = std::stof(priceGame_str);
            int gamesInStock = std::stof(gamesInStock_str);

            // Lưu vào mảng
            games[idx++] = Game(idGame, nameGame, genre, priceGame, gamesInStock);
        }
    }
    return games;
}

void FileManager::saveCustomer(const std::string& fileCustomer, Customer& customer)
{
    std::ofstream file(fileCustomer, std::ios::app);
    if (file.is_open()) {
        file << customer.getCustomerID() << '|'
             << customer.getCustomerName() << '|'
             << customer.getEmail() << '|'
             << customer.getPhone() << '|'
             << customer.getUserName() << '|'
             << customer.getPassword() << std::endl;
    }
}