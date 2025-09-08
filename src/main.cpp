#include <iostream>
#include "RestaurantBillingSystem.h"

int main() {
    RestaurantBillingSystem billingSystem;
    std::cout << "Welcome to Restaurant Billing System!" << std::endl;

    while (true) {
        billingSystem.displayMainMenu();
        int choice = 0;
        std::cout << "Enter your choice (1-10): ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input.\n";
            RestaurantBillingSystem::clearInput();
            continue;
        }

        switch (choice) {
            case 1:
                billingSystem.displayMenu();
                break;
            case 2: {
                int itemId = RestaurantBillingSystem::readInt("Enter item ID: ", 1, 1000000);
                int quantity = RestaurantBillingSystem::readInt("Enter quantity: ", 1, 1000);
                billingSystem.addItemToOrder(itemId, quantity);
                break;
            }
            case 3:
                billingSystem.displayCurrentOrder();
                break;
            case 4: {
                int itemId = RestaurantBillingSystem::readInt("Enter item ID to remove: ", 1, 1000000);
                billingSystem.removeItemFromOrder(itemId);
                break;
            }
            case 5:
                billingSystem.generateBill(true, true);
                break;
            case 6:
                billingSystem.clearOrder();
                break;
            case 7: {
                int itemId = RestaurantBillingSystem::readInt("Enter item ID to update: ", 1, 1000000);
                int newQty = RestaurantBillingSystem::readInt("New quantity: ", 1, 1000);
                billingSystem.updateItemQuantity(itemId, newQty);
                break;
            }
            case 8:
                billingSystem.applyDiscountMenu();
                break;
            case 9:
                billingSystem.configureRates();
                break;
            case 10:
                std::cout << "Thank you for using Restaurant Billing System!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                break;
        }

        RestaurantBillingSystem::pause();
    }

    return 0;
}