#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>

class MenuItem {
public:
    int id;
    std::string name;
    double price;
    std::string category;

    MenuItem(int id, const std::string& name, double price, const std::string& category)
        : id(id), name(name), price(price), category(category) {}
};

#endif // MENU_ITEM_H