#include "D:\PBL2_GAMESTORE\include\Customer.h"
#include "D:\PBL2_GAMESTORE\include\FileManager.h"
#include "D:\PBL2_GAMESTORE\include\Products.h"
#include "D:\PBL2_GAMESTORE\include\Order.h"
#include "D:\PBL2_GAMESTORE\include\Admin.h"
#include <iostream>

using namespace std;

int main()
{
    Customer *customers = new Customer;
    Products *products = new Products;
    Order *orders = new Order;
    Admin *admin = new Admin;

    int option;
    bool InOut = true;
    while(InOut) {
        cout << "\t\t\t THE GIOI CONG NGHE \t\t\t";
        cout << "\n\n";
        cout << "1. Login. \n";
        cout << "2. Register. \n";
        cout << "0. Exit. \n";
        cout << "Enter choice: ";
        cin >> option;

        bool tinhNang = true;
        switch(option) {
            case 1:
            {
                int dangNhap = customers->login(customers);
                if (dangNhap == 2) {
                    // day la admin
                    while(tinhNang) {
                        cout << endl;
                        cout << "1. Display customers. \n";
                        cout << "2. Display orders. \n";
                        cout << "3. Add product. \n";
                        cout << "4. Delete product. \n";
                        cout << "5. Edit product. \n";
                        cout << "0. Logout. \n";
                        cout << "Enter choice: ";
                        int choice; cin >> choice;

                        switch(choice) {
                            case 1: 
                            {
                                customers->displayCustomer();
                            }
                                break;
                            case 2:
                            {
                                orders->displayOrder();
                            }
                                break;
                            case 3:
                                admin->addProduct();
                                break;
                            case 4:
                                admin->deleteProduct();
                                break;
                            case 5:
                                admin->editProduct();
                                break;
                            case 0:
                            {
                                cout << "Logout successfully. \n";
                                tinhNang = false;
                            }
                                break;
                            default:
                                cout << "Invalid choice !\n";
                                break;
                        }
                    }
                }
                else if (dangNhap == 1) {
                    // Nếu là khách hàng 
                    while(tinhNang) {
                        cout << endl;
                        cout << "1. Update info. \n";
                        cout << "2. Display Order. \n";
                        cout << "3. Change password. \n";
                        cout << "4. Add to cart. \n";
                        cout << "5. Display specification. \n";
                        cout << "6. Display products. \n";
                        cout << "0. Logout. \n";
                        cout << "Enter choice: ";
                        int choice; cin >> choice;

                        switch(choice) {
                            case 1:
                                customers->updateCustomerInfo();
                                break;
                            case 2:
                                orders->displayOrder();
                                break;
                            case 3:
                                customers->changePassword();
                                break;
                            case 4:
                                orders->addData(101, "iPhone 15 Pro Max", "Dien Thoai", "Apple", "iOS", 1299, 2);
                                break;
                            case 5:
                                int productID;
                                cout << "Which product do you want to see the technical specifications of ? \n";
                                cout << "Enter choice: ";
                                cin >> productID;
                                products->displaySpecification(productID);
                                break;
                            case 6:
                                products->displayProducts();
                                break;
                            case 0:
                                cout << "Logout successfully.\n";
                                tinhNang = false;
                                break;
                            default:
                                cout << "Invalid choice !\n";
                                break;
                        }
                    }
                } else {
                    cout << "Account not found. \n";
                }
            }
                break;
            case 2:
            {
                customers = new Customer;
                customers->registerAccount();
                break;
            }

            case 0:
            {
                cout << "Bye bye.\n";
                InOut = false;
                break;
            }
            default:
                cout << "Invalid option. \n";
                break;
        }
    }
    delete customers;
    delete products;
    delete orders;
    delete admin;
    return 0;
}