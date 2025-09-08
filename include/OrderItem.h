#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H
#include <string>
class OrderItem {
public:
    int itemId;
    std::string name;
    double price;
    int quantity;
    double total;
    OrderItem(int itemId, const std::string& name, double price, int quantity)
        : itemId(itemId), name(name), price(price), quantity(quantity), total(price * quantity) {}
    void calculateTotal() { total = price * quantity; }
};
#endif