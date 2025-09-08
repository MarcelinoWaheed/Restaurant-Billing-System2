#ifndef RESTAURANT_BILLING_SYSTEM_H
#define RESTAURANT_BILLING_SYSTEM_H

#include <vector>
#include <string>
#include "MenuItem.h"
#include "OrderItem.h"

class RestaurantBillingSystem
{
private:
    std::vector<MenuItem> menu;
    std::vector<OrderItem> currentOrder;
    double taxRate;
    double serviceCharge;
    double discountPercent;
    std::string appliedPromo;

    void initializeMenu();
    const MenuItem *findMenuItem(int itemId) const;
    static std::string money(double v);

public:
    // public helpers for safe IO
    static void clearInput();
    static int readInt(const std::string &prompt, int minV, int maxV);
    static double readDouble(const std::string &prompt, double minV, double maxV);
    static void pause();

    RestaurantBillingSystem();

    void setRates(double taxPct, double svcPct);
    void displayMenu() const;
    void displayCurrentOrder() const;
    bool addItemToOrder(int itemId, int quantity);
    bool updateItemQuantity(int itemId, int newQty);
    bool removeItemFromOrder(int itemId);
    void clearOrder();
    double calculateSubtotal() const;
    void applyDiscountMenu();
    void configureRates();
    void generateBill(bool saveReceipt = true, bool handlePayment = true) const;
    void displayMainMenu() const;

    bool isOrderEmpty() const { return currentOrder.empty(); }
    int getOrderSize() const { return (int)currentOrder.size(); }
};

#endif // RESTAURANT_BILLING_SYSTEM_H