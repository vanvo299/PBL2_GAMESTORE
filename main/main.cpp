#include "D:\PBL2_GAMESTORE\include\Customer.h"
#include "D:\PBL2_GAMESTORE\include\FileManager.h"
#include "D:\PBL2_GAMESTORE\include\Game.h"
#include "D:\PBL2_GAMESTORE\include\Products.h"
#include "D:\PBL2_GAMESTORE\include\Order.h"
#include <iostream>

using namespace std;

int main()
{
    Customer *customers = new Customer;
    Game *games = new Game;
    Products *products = new Products;
    Order *orders = new Order;
    int option;
    bool InOut = true;
    while(InOut) {
        cout << "\t\t\tCUA HANG SACH\t\t\t";
        cout << "\n\n";
        cout << "1. Login.\n";
        cout << "2. Register.\n";
        cout << "0. Exit.\n";
        cout << "Enter choice: ";
        cin >> option;

        // bool check = false;
        bool tinhNang = true;
        switch (option)
        {
        case 1:
        {
            // customers = new Customer;
            bool dangNhap = customers->login(customers);
            if (dangNhap) {
                // check = true;
                while(tinhNang) {
                    cout << endl;
                    cout << "1. Display book. \n";
                    cout << "2. Display customers.\n";
                    cout << "3. Update info. \n";
                    cout << "4. Display Products. \n";
                    cout << "5. Display Order. \n";
                    cout << "6. Change password. \n";
                    cout << "7. Add to cart. \n";
                    cout << "0. Logout.\n";
                    cout << "Enter choice: ";
                    int choice; cin >> choice;

                    switch (choice)
                    {
                    case 1:
                    {
                        games = new Game;
                        games->displayGame();
                    }
                        break;
                    case 2:
                    {
                        customers->displayCustomer();
                    }
                        break;
                    case 3:
                    {
                        customers->updateCustomerInfo();
                    }
                        break;
                    case 4:
                    {
                        products->displayProducts();
                    }
                        break;
                    case 5:
                    {
                        orders->displayOrder();
                    }
                        break;
                    case 6: 
                    {
                        customers->changePassword();
                    }
                        break;
                    case 7: 
                    {
                        orders->addData(101, "iPhone 15 Pro Max", "Dien Thoai", "Apple", "iOS", 1299, 2);
                        // orders->addData(102, "Samsung Galaxy S24 Ultra", "Dien Thoai", "Samsung", "iOS", 1299, 2);

                    }
                        break;
                    case 0:
                        cout << "Logout successfully. \n";
                        tinhNang = false;
                        break;
                    default:
                        cout << "Invalid choice !\n";
                        break;
                    }
                }
            } else {
                std::cout << "Account not found. \n";
            }
            break;
        }

        case 2:       
        {
            customers = new Customer;
            customers->registerAccount();
            break;
        }

        case 0: 
        {
            cout << "Bye Bye. \n";
            InOut = false;
            break;
        }

        default:
            cout << "Invalid option.\n";
            break;
        }
    }
    
    delete customers;
    delete games;
    delete products;
    delete orders;
    return 0;
}