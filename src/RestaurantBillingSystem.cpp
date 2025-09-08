#include "RestaurantBillingSystem.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <fstream>
#include <sstream>

static std::string hr(int n, char c = '=') {
    return std::string(n, c);
}

RestaurantBillingSystem::RestaurantBillingSystem()
    : taxRate(0.10), serviceCharge(0.05), discountPercent(0.0) {
    initializeMenu();
}

void RestaurantBillingSystem::initializeMenu() {
    menu.emplace_back(1, "Chicken Wings", 8.99, "Appetizers");
    menu.emplace_back(2, "Mozzarella Sticks", 6.99, "Appetizers");
    menu.emplace_back(3, "Caesar Salad", 7.99, "Appetizers");

    menu.emplace_back(4, "Grilled Chicken", 15.99, "Main Course");
    menu.emplace_back(5, "Beef Burger", 12.99, "Main Course");
    menu.emplace_back(6, "Fish & Chips", 14.99, "Main Course");
    menu.emplace_back(7, "Pasta Carbonara", 13.99, "Main Course");
    menu.emplace_back(8, "Pizza Margherita", 11.99, "Main Course");

    menu.emplace_back(9, "Coca Cola", 2.99, "Beverages");
    menu.emplace_back(10, "Fresh Juice", 4.99, "Beverages");
    menu.emplace_back(11, "Coffee", 3.99, "Beverages");
    menu.emplace_back(12, "Tea", 2.49, "Beverages");

    menu.emplace_back(13, "Chocolate Cake", 5.99, "Desserts");
    menu.emplace_back(14, "Ice Cream", 4.99, "Desserts");
    menu.emplace_back(15, "Cheesecake", 6.99, "Desserts");

    std::sort(menu.begin(), menu.end(), [](const MenuItem& a, const MenuItem& b){
        if (a.category == b.category) return a.id < b.id;
        return a.category < b.category;
    });
}

const MenuItem* RestaurantBillingSystem::findMenuItem(int itemId) const {
    auto it = std::find_if(menu.begin(), menu.end(),
                           [itemId](const MenuItem& item) { return item.id == itemId; });
    return it == menu.end() ? nullptr : &(*it);
}

std::string RestaurantBillingSystem::money(double v) {
    std::ostringstream os;
    os << "$" << std::fixed << std::setprecision(2) << v;
    return os.str();
}

void RestaurantBillingSystem::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int RestaurantBillingSystem::readInt(const std::string& prompt, int minV, int maxV) {
    while (true) {
        std::cout << prompt;
        int v;
        if (std::cin >> v && v >= minV && v <= maxV) return v;
        std::cout << "Invalid input.\n";
        clearInput();
    }
}

double RestaurantBillingSystem::readDouble(const std::string& prompt, double minV, double maxV) {
    while (true) {
        std::cout << prompt;
        double v;
        if (std::cin >> v && v >= minV && v <= maxV) return v;
        std::cout << "Invalid input.\n";
        clearInput();
    }
}

void RestaurantBillingSystem::pause() {
    std::cout << "\nPress Enter to continue...";
    clearInput();
    std::cin.get();
}

void RestaurantBillingSystem::setRates(double taxPct, double svcPct) {
    taxRate = taxPct;
    serviceCharge = svcPct;
}

void RestaurantBillingSystem::displayMenu() const {
    std::cout << "\n" << hr(60) << std::endl;
    std::cout << "                    RESTAURANT MENU" << std::endl;
    std::cout << hr(60) << std::endl;

    std::string currentCategory;
    for (const auto& item : menu) {
        if (item.category != currentCategory) {
            currentCategory = item.category;
            std::cout << "\n" << currentCategory << ":" << std::endl;
            std::cout << hr(40, '-') << std::endl;
        }
        std::cout << std::setw(3) << item.id << ". "
                  << std::setw(25) << std::left << item.name
                  << money(item.price) << std::endl;
    }
    std::cout << hr(60) << std::endl;
}

void RestaurantBillingSystem::displayCurrentOrder() const {
    if (currentOrder.empty()) {
        std::cout << "\nNo items in current order." << std::endl;
        return;
    }

    std::cout << "\n" << hr(60) << std::endl;
    std::cout << "                    CURRENT ORDER" << std::endl;
    std::cout << hr(60) << std::endl;
    std::cout << std::left
              << std::setw(4) << "ID"
              << std::setw(24) << "Item"
              << std::setw(6) << "Qty"
              << std::setw(12) << "Price"
              << std::setw(12) << "Total"
              << std::endl;
    std::cout << hr(60, '-') << std::endl;

    for (const auto& item : currentOrder) {
        std::cout << std::left
                  << std::setw(4) << item.itemId
                  << std::setw(24) << item.name.substr(0, 23)
                  << std::setw(6) << item.quantity
                  << std::setw(12) << money(item.price)
                  << std::setw(12) << money(item.total)
                  << std::endl;
    }
    std::cout << hr(60) << std::endl;
    std::cout << "Subtotal: " << money(calculateSubtotal()) << std::endl;
}

bool RestaurantBillingSystem::addItemToOrder(int itemId, int quantity) {
    const MenuItem* it = findMenuItem(itemId);
    if (!it) {
        std::cout << "Item not found!" << std::endl;
        return false;
    }
    if (quantity <= 0) {
        std::cout << "Quantity must be positive!" << std::endl;
        return false;
    }

    auto orderIt = std::find_if(currentOrder.begin(), currentOrder.end(),
                                [itemId](const OrderItem& item) { return item.itemId == itemId; });

    if (orderIt != currentOrder.end()) {
        orderIt->quantity += quantity;
        orderIt->calculateTotal();
        std::cout << "Updated quantity for " << it->name << std::endl;
    } else {
        currentOrder.emplace_back(it->id, it->name, it->price, quantity);
        std::cout << "Added " << quantity << "x " << it->name << " to order" << std::endl;
    }
    return true;
}

bool RestaurantBillingSystem::updateItemQuantity(int itemId, int newQty) {
    auto it = std::find_if(currentOrder.begin(), currentOrder.end(),
                           [itemId](const OrderItem& item) { return item.itemId == itemId; });
    if (it == currentOrder.end()) {
        std::cout << "Item not in order!" << std::endl;
        return false;
    }
    if (newQty <= 0) {
        std::cout << "Quantity must be positive!" << std::endl;
        return false;
    }
    it->quantity = newQty;
    it->calculateTotal();
    std::cout << "Quantity updated.\n";
    return true;
}

bool RestaurantBillingSystem::removeItemFromOrder(int itemId) {
    auto it = std::find_if(currentOrder.begin(), currentOrder.end(),
                           [itemId](const OrderItem& item) { return item.itemId == itemId; });

    if (it == currentOrder.end()) {
        std::cout << "Item not found in order!" << std::endl;
        return false;
    }

    std::cout << "Removed " << it->name << " from order" << std::endl;
    currentOrder.erase(it);
    return true;
}

void RestaurantBillingSystem::clearOrder() {
    currentOrder.clear();
    discountPercent = 0.0;
    appliedPromo.clear();
    std::cout << "Order cleared!" << std::endl;
}

double RestaurantBillingSystem::calculateSubtotal() const {
    double subtotal = 0.0;
    for (const auto& item : currentOrder) subtotal += item.total;
    return subtotal;
}

void RestaurantBillingSystem::applyDiscountMenu() {
    std::cout << "Discount options:\n";
    std::cout << "0) None  1) Percent  2) Promo (SAVE10)\n";
    int d = readInt("Select: ", 0, 2);
    discountPercent = 0.0;
    appliedPromo.clear();
    if (d == 1) {
        discountPercent = readDouble("Percent (0-100): ", 0.0, 100.0);
    } else if (d == 2) {
        std::string code;
        std::cout << "Enter code: ";
        std::cin >> code;
        if (code == "SAVE10") {
            discountPercent = 10.0;
            appliedPromo = code;
        } else {
            std::cout << "Invalid code.\n";
        }
    }
    std::cout << "Discount set to " << discountPercent << "%\n";
}

void RestaurantBillingSystem::configureRates() {
    double t = readDouble("Tax percent (current " + std::to_string(int(taxRate * 100)) + "%): ", 0.0, 100.0);
    double s = readDouble("Service percent (current " + std::to_string(int(serviceCharge * 100)) + "%): ", 0.0, 100.0);
    setRates(t / 100.0, s / 100.0);
    std::cout << "Rates updated.\n";
}

void RestaurantBillingSystem::generateBill(bool saveReceipt, bool handlePayment) const {
    if (currentOrder.empty()) {
        std::cout << "\nNo items to bill!" << std::endl;
        return;
    }

    double subtotal = calculateSubtotal();
    double discount = subtotal * (discountPercent / 100.0);
    double afterDisc = subtotal - discount;
    double tax = afterDisc * taxRate;
    double service = afterDisc * serviceCharge;
    double total = afterDisc + tax + service;

    std::ostringstream receipt;
    receipt << "\n" << hr(60) << "\n";
    receipt << "                    RESTAURANT BILL\n";
    receipt << hr(60) << "\n";
    receipt << std::left
            << std::setw(4) << "ID"
            << std::setw(24) << "Item"
            << std::setw(6) << "Qty"
            << std::setw(12) << "Price"
            << std::setw(12) << "Total" << "\n";
    receipt << hr(60, '-') << "\n";

    for (const auto& item : currentOrder) {
        receipt << std::left
                << std::setw(4) << item.itemId
                << std::setw(24) << item.name.substr(0, 23)
                << std::setw(6) << item.quantity
                << std::setw(12) << money(item.price)
                << std::setw(12) << money(item.total)
                << "\n";
    }

    receipt << hr(60, '-') << "\n";
    receipt << std::setw(45) << std::right << "Subtotal:" << " " << money(subtotal) << "\n";
    receipt << std::setw(45) << std::right << ("Discount (" + std::to_string(discountPercent) + "%):") << " -" << money(discount) << "\n";
    receipt << std::setw(45) << std::right << ("Tax (" + std::to_string(int(taxRate * 100)) + "%):") << " " << money(tax) << "\n";
    receipt << std::setw(45) << std::right << ("Service (" + std::to_string(int(serviceCharge * 100)) + "%):") << " " << money(service) << "\n";
    receipt << hr(60) << "\n";
    receipt << std::setw(45) << std::right << "TOTAL:" << " " << money(total) << "\n";
    receipt << hr(60) << "\n";

    std::cout << receipt.str();

    if (saveReceipt) {
        std::ofstream rf("receipt.txt");
        if (rf.is_open()) {
            rf << receipt.str();
            std::cout << "Saved receipt.txt\n";
        }
    }

    if (handlePayment) {
        std::cout << "Payment method: 1) Cash  2) Card  3) UPI\n";
        int pm = readInt("Select: ", 1, 3);
        if (pm == 1) {
            double cash = readDouble("Cash received: ", total, 1e9);
            std::cout << "Change: " << money(cash - total) << "\n";
        } else {
            std::cout << "Payment authorized.\n";
        }
    }

    int guests = readInt("Split bill - number of guests (1-50): ", 1, 50);
    if (guests > 1) {
        std::cout << "Per guest: " << money(total / guests) << "\n";
    }
}

void RestaurantBillingSystem::displayMainMenu() const {
    std::cout << "\n" << hr(40) << std::endl;
    std::cout << "     RESTAURANT BILLING SYSTEM" << std::endl;
    std::cout << hr(40) << std::endl;
    std::cout << "1. View Menu" << std::endl;
    std::cout << "2. Add Item to Order" << std::endl;
    std::cout << "3. View Current Order" << std::endl;
    std::cout << "4. Remove Item from Order" << std::endl;
    std::cout << "5. Generate Bill" << std::endl;
    std::cout << "6. Clear Order" << std::endl;
    std::cout << "7. Update Item Quantity" << std::endl;
    std::cout << "8. Apply Discount" << std::endl;
    std::cout << "9. Configure Tax/Service Rates" << std::endl;
    std::cout << "10. Exit" << std::endl;
    std::cout << hr(40) << std::endl;
}