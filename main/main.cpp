#include "D:\PBL2_GAMESTORE\include\Customer.h"
#include "D:\PBL2_GAMESTORE\include\FileManager.h"
#include "D:\PBL2_GAMESTORE\include\Game.h"
#include <iostream>
using namespace std;

int main()
{
    Customer *customers = NULL;
    Game *games = NULL;
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

        bool check = false;
        bool tinhNang = true;
        switch (option)
        {
        case 1:
        {
            customers = new Customer;
            bool dangNhap = customers->login();
            if (dangNhap) {
                check = true;
                while(tinhNang) {
                    cout << endl;
                    cout << "1. Display book. \n";
                    cout << "2. Display customers.\n";
                    cout << "3. Update info. \n";
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
                        customers = new Customer;
                        customers->displayCustomer();
                    }
                        break;
                    case 3:
                    {
                        customers = new Customer;
                        customers->updateCustomerInfo(customers);
                    }
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
    return 0;
}